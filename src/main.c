#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include"../inc/cpu.h"
#include"../inc/rv_cpu.h"
#include"../inc/rv_disp.h"



int main () {
  cpu_t vm;
  
  rv_cpu_arch_desc_t rv_desc_32i = {
    .dispatcher = rv_32i_dispatcher,
    .mem_sz = 4096U,
    .pc = 32U
  };

  cpu_arch_t rv32i = {
    .desc = (cpu_arch_desc_t)&rv_desc_32i,
    .init = init_rv_cpu,
    .exec = exec_rv_cpu,
    .free = free_rv_cpu
  };

  init_cpu(&vm, &rv32i);

  exec_cpu(&vm);

  free_cpu(&vm);

  return 0;
}
