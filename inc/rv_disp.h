#pragma once
#include<stdint.h>
#include<string.h>
#include"rv_cpu.h"
#include"rv_types.h"


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

void rv_32i_dispatcher (cpu_state_t state, rv_instr_t instr);
