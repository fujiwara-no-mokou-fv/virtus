#include<stdint.h>
#include"../inc/cpu.h"

void init_cpu(cpu_t *cpu, cpu_arch_t *arch){
  cpu->exec = arch->exec;
  cpu->free = arch->free;
  arch->init(&cpu->state, arch->desc);
}

void exec_cpu(cpu_t *cpu){
  cpu->exec(cpu->state);
}

void free_cpu(cpu_t *cpu){
  cpu->free(cpu->state);
}
