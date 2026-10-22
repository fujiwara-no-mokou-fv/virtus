#pragma once
#include<stdint.h>
#include<string.h>
#include"rv_cpu.h"



typedef struct {
  size_t width;
  size_t offset;
} rv_field_desc_t;

constexpr rv_field_desc_t OP = {
  .width = 7U,
  .offset = 0
};

constexpr rv_field_desc_t RD = {
  .width = 5U,
  .offset = 7
};

constexpr rv_field_desc_t F3 = {
  .width = 3U,
  .offset = 12
};

constexpr rv_field_desc_t RS1 = {
  .width = 5U,
  .offset = 15
};

constexpr rv_field_desc_t RS2 = {
  .width = 5U,
  .offset = 20
};

constexpr rv_field_desc_t F7 = {
  .width = 7U,
  .offset = 25
};

constexpr rv_field_desc_t F7_BIT5 = {
  .width = 1U,
  .offset = 30
};

constexpr rv_field_desc_t I_IMM = {
  .width = 12,
  .offset = 20
};

typedef struct {
  uint32_t raw;
} rv_instr_t;

typedef struct {
  uint32_t raw;
} rv_imm_t;

typedef struct {
  uint32_t val;
} rv_opcode_t;

typedef struct {
  uint32_t val;
} rv_func_t;

typedef struct {
  uint32_t val;
} rv_x_reg_index_t;

typedef struct {
  int32_t val;
} rv_i_imm_t;

typedef union {
  rv_opcode_t opcode;
  rv_func_t func;
  rv_x_reg_index_t index;
  rv_imm_t imm;
  uint32_t raw;
} rv_field_t;

[[gnu::always_inline]] static inline rv_field_t get_rv_field (
    rv_instr_t instr,
    rv_field_desc_t desc){
  rv_field_t field;
  field.raw = (instr.raw >> desc.offset) & ((1U << desc.width) - 1U);
  
  return field;
}

[[gnu::always_inline]] static inline rv_i_imm_t extr_i_imm (rv_imm_t imm) {
  return (rv_i_imm_t){.val = (int32_t)(imm.raw << 20) >> 20};
}

typedef void (*rv_handler_t)(rv_cpu_state_t *state, rv_instr_t instr);

typedef void (*rv_exec_t)(rv_cpu_state_t *state, rv_instr_t instr);

typedef struct {
  rv_handler_t rv_handler[128U];
} rv_dec_t;

extern rv_dec_t rv_dec;

