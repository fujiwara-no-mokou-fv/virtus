#pragma once
#include<stdint.h>
#include<string.h>
#include"cpu.h"



constexpr size_t CACHE_LINE = 64U;
constexpr size_t MEM_PAGE = 2048U;

typedef void *dec_t;

typedef struct [[gnu::aligned(64)]] {
  dec_t dec;
  uint8_t *mem;
  uint32_t x_reg [32];
  uint32_t pc;
} rv_cpu_state_t;

constexpr size_t RV_CPU_STATE_SZ = sizeof(rv_cpu_state_t);

typedef struct {
  dec_t dec;
  uint32_t mem_sz;
  uint32_t pc;
} rv_cpu_arch_desc_t;

void init_rv_cpu(cpu_state_t *state, cpu_arch_desc_t desc);

void exec_rv_cpu(cpu_state_t state);

void free_rv_cpu(cpu_state_t state);
