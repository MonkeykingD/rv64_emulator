/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"
int gpr_len=sizeof(cpu.gpr)/sizeof(cpu.gpr[0]);
bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {

  for(int i=0;i<gpr_len;i++){
    if(cpu.gpr[i]!=ref_r->gpr[i])
    {
      printf("ref reg[%0d]: %0lx not match with dut reg[%0d]: %0lx at pc:%0lx\n",i,ref_r->gpr[i],i,cpu.gpr[i],pc);
      return false;
    }
  }
  return true;
}

void isa_difftest_attach() {
}
