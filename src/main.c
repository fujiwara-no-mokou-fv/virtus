#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"decoder.h"



uint32_t i = 0b000000000000'00011'000'01000'0110011ull; // addi x8 x3 1

int main () {
  printf("opcode =%#x\n",getf(OP, i));
  printf("rd =\tx%d\n",getf(RD, i));
  printf("func3 =\t%#x\n",getf(F3, i));
  printf("rs1 =\tx%d\n",getf(RS1, i));
  printf("imm =\t%d\n",dec_imm_i(i));
  //printf("func7 =\t%#x\n",getf(F7, i));
  return 0;
}
