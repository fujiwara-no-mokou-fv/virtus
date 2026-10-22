#include<stdint.h>
#include<string.h>
#include"../inc/rv_cpu.h"
#include"../inc/rv_dec.h"



[[gnu::always_inline]] static inline rv_instr_t fetch_rv_instr(
    rv_cpu_state_t *state) {

  rv_instr_t instr;
  memcpy(&instr.raw, &state->mem[state->pc], sizeof(rv_instr_t));
  
  return instr;
}

void halt(rv_cpu_state_t *state, rv_instr_t instr) {
  return;
}

void add(rv_cpu_state_t *state, rv_instr_t instr) { 
  rv_x_reg_index_t rd = get_rv_field(instr, RD).index;
  rv_x_reg_index_t rs1 = get_rv_field(instr, RS1).index;
  rv_x_reg_index_t rs2 = get_rv_field(instr, RS2).index;
  
  if(rd.val != 0) {
  state->x_reg[rd.val] = state->x_reg[rs1.val] + state->x_reg[rs2.val];
  }

  state->pc += sizeof(rv_instr_t);
  rv_instr_t next_instr = fetch_rv_instr(state);
  
  auto dec = (rv_dec_t *)(state->dec);
  
  [[gnu::musttail]] return dec->rv_handler[
    get_rv_field(next_instr, OP).opcode.val](
      state,
      next_instr);
}

void rv_handler_0x33(rv_cpu_state_t *state, rv_instr_t instr) {
  static const rv_exec_t exec[16U] = {
    [0U ... 15U] = halt,
    [0x00] = add
  };

  [[gnu::musttail]] return exec[
    get_rv_field(instr, F7_BIT5).func.val << 3U 
    | (get_rv_field(instr, F3).func.val)](
      state,
      instr);
}

void addi(rv_cpu_state_t *state, rv_instr_t instr) {
  rv_x_reg_index_t rd = get_rv_field(instr, RD).index;
  rv_x_reg_index_t rs1 = get_rv_field(instr, RS1).index;
  rv_imm_t imm = get_rv_field(instr, I_IMM).imm;
  rv_i_imm_t i_imm = extr_i_imm(imm);

  if(rd.val != 0) {
  state->x_reg[rd.val] = state->x_reg[rs1.val] + i_imm.val;
  }

  state->pc += sizeof(rv_instr_t);

  rv_instr_t next_instr = fetch_rv_instr(state);
  
  auto dec = (rv_dec_t *)(state->dec);
  
  [[gnu::musttail]] return dec->rv_handler[
    get_rv_field(next_instr, OP).opcode.val](
    state,
    next_instr);
}

void rv_handler_0x13(rv_cpu_state_t *state, rv_instr_t instr) {
  static const rv_exec_t exec [8U] = {
    [0U ... 7U] = halt,
    [0x00] = addi
  };

  [[gnu::musttail]] return exec[get_rv_field(instr, F3).func.val](
    state,
    instr);
}

rv_dec_t rv_dec = {
  .rv_handler = {
    [0U ... 127U] = halt,	  
    [0x33] = rv_handler_0x33,
    [0x13] = rv_handler_0x13
  }
};

