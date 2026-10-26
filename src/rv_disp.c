#include<stdint.h>
#include<string.h>
#include"../inc/rv_cpu.h"
#include"../inc/rv_disp.h"
#include"../inc/rv_types.h"



void halt(cpu_state_t state, rv_instr_t instr) {
  return;
}

void add(cpu_state_t state, rv_instr_t instr) { 
  auto rv_state = (rv_cpu_state_t *)state;
  rv_x_reg_index_t rd = get_rv_field(instr, RD).index;
  rv_x_reg_index_t rs1 = get_rv_field(instr, RS1).index;
  rv_x_reg_index_t rs2 = get_rv_field(instr, RS2).index;
  
  if(rd.val != 0) {
  rv_state->x_reg[rd.val] = rv_state->x_reg[rs1.val] + rv_state->x_reg[rs2.val];
  }

  rv_state->pc += sizeof(rv_instr_t);
  rv_instr_t next_instr = fetch_rv_instr(rv_state);
  
  [[gnu::musttail]] return rv_state->dispatcher(
      rv_state,
      next_instr);
}

void addi(cpu_state_t state, rv_instr_t instr) {
  auto rv_state = (rv_cpu_state_t *)state;
  rv_x_reg_index_t rd = get_rv_field(instr, RD).index;
  rv_x_reg_index_t rs1 = get_rv_field(instr, RS1).index;
  rv_imm_t imm = get_rv_field(instr, I_IMM).imm;
  rv_i_imm_t i_imm = extr_i_imm(imm);

  if(rd.val != 0) {
  rv_state->x_reg[rd.val] = rv_state->x_reg[rs1.val] + i_imm.val;
  }

  rv_state->pc += sizeof(rv_instr_t);

  rv_instr_t next_instr = fetch_rv_instr(rv_state);
  
  [[gnu::musttail]] return rv_state->dispatcher(
    rv_state,
    next_instr);
}

void rv_dispatch_0x33(cpu_state_t state, rv_instr_t instr) {
  static const rv_dispatch_t dispatch[16U] = {
    [0U ... 15U] = halt,
    [0x00] = add
  };

  [[gnu::musttail]] return dispatch[
    get_rv_field(instr, F7_BIT5).func.val << 3U 
    | (get_rv_field(instr, F3).func.val)](
      state,
      instr);
}

void rv_dispatch_0x13(cpu_state_t state, rv_instr_t instr) {
  static const rv_dispatch_t dispatch[8U] = {
    [0U ... 7U] = halt,
    [0x00] = addi
  };
  [[gnu::musttail]] return dispatch[get_rv_field(instr, F3).func.val](
    state,
    instr);
}

void rv_32i_dispatcher (cpu_state_t state, rv_instr_t instr) {
  static const rv_dispatch_t dispatch[128U] = {
    [0U ... 127U] = halt,	  
    [0x33] = rv_dispatch_0x33,
    [0x13] = rv_dispatch_0x13
  };
  [[gnu::musttail]] return dispatch[get_rv_field(instr, OP).opcode.val](
      state,
      instr);
}
