#pragma once
#include<stdint.h>



typedef void *cpu_state_t;
typedef void *cpu_arch_desc_t;
typedef void (*init_t)(cpu_state_t *state, cpu_arch_desc_t desc);
typedef void (*exec_t)(cpu_state_t state);
typedef void (*free_t)(cpu_state_t state);

typedef struct {
  cpu_state_t state;
  exec_t exec;
  free_t free;
} cpu_t;

typedef struct {
  cpu_arch_desc_t desc;
  init_t init;
  exec_t exec;
  free_t free;
} cpu_arch_t;

void init_cpu(cpu_t *cpu, cpu_arch_t *arch);

void exec_cpu(cpu_t *cpu);

void free_cpu(cpu_t *cpu);
