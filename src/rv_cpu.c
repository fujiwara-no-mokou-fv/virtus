#include<stdint.h>
#include<stdlib.h>
#include"../inc/rv_cpu.h"
#include"../inc/rv_types.h"



[[gnu::always_inline]] static inline rv_instr_t fetch_rv_instr(rv_cpu_state_t *state) {
  rv_instr_t instr;
  state->x_reg[0] = 0;
  memcpy(&instr.raw, &state->mem[state->pc], sizeof(uint32_t));
  return instr;
}

void init_rv_cpu(cpu_state_t *state, cpu_arch_desc_t desc) {
  auto rv_desc = (rv_cpu_arch_desc_t *)desc;
  rv_cpu_state_t *rv_state;

  rv_state = aligned_alloc(CACHE_LINE, RV_CPU_STATE_SZ);

  if(rv_state == nullptr) {
    *state = nullptr;
    return;
  }

  memset(rv_state, 0, RV_CPU_STATE_SZ);

  rv_state->mem = aligned_alloc(MEM_PAGE, rv_desc->mem_sz);
  
  if(rv_state->mem == nullptr) {
    free(rv_state);
    *state = nullptr;
    return;
  }
  
  memset(rv_state->mem, 0, rv_desc->mem_sz);
  
  if(rv_desc->pc > rv_desc->mem_sz || sizeof(rv_instr_t) > rv_desc->mem_sz) {
    free(rv_state->mem);
    free(rv_state);
    *state = nullptr;
    return;
  }
  rv_state->pc = rv_desc->pc;

  if(rv_desc->dispatcher == nullptr) {
  free(rv_state->mem);
  free(rv_state);
  *state = nullptr;
  return;
  }
  rv_state->dispatcher = rv_desc->dispatcher;
  
  *state = (cpu_state_t)rv_state;
}

void exec_rv_cpu(cpu_state_t state) {
  auto rv_state = (rv_cpu_state_t *)state;
  rv_instr_t first_instr = fetch_rv_instr(rv_state);
  rv_state->dispatcher(state, first_instr);
}

void free_rv_cpu(cpu_state_t state) {
  auto rv_state = (rv_cpu_state_t *)state;
  free(rv_state->mem);
  free(rv_state);
}
