#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include"../inc/cpu.h"
#include"../inc/rv_cpu.h"
#include"../inc/rv_dec.h"



const uint32_t instr = 0b0000000'00100'00101'000'00001'0110011;

int main () {
  rv_cpu_arch_desc_t rv32i_desc = {
    .dec = (dec_t)&rv_dec,
    .mem_sz = 4096U,
    .pc = 256U
  };
  cpu_t rv32i;
  cpu_arch_t rv32i_arch = {
    .desc = (cpu_arch_desc_t)&rv32i_desc,
    .init = init_rv_cpu,
    .exec = exec_rv_cpu,
    .free = free_rv_cpu
  };
  init_cpu(&rv32i, &rv32i_arch);
  memcpy(&(((rv_cpu_state_t *)(rv32i.state))->mem[256U]), &instr, sizeof instr);
  exec_cpu(&rv32i);
  free_cpu(&rv32i);
  return 0;
}
