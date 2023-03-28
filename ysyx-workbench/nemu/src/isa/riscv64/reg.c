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
#include "local-include/reg.h"
//CPU_state cpu= {};
const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};
int regs_len=sizeof(regs)/sizeof(regs[0]);
void isa_reg_display() {
  for (int i = 0; i < regs_len; i ++) {
   printf("%-s\t",regs[i]);
   printf(FMT_WORD,cpu.gpr[i]);
   printf("\n");
  }
}

word_t isa_reg_str2val(const char *s, bool *success) {
  if(strcmp(s,"$pc")==0){
    *success=true;
    return cpu.pc;    
  }
  for (int i = 0; i < regs_len; i ++) {
    if(s[1]!='0'){
      if(strcmp(s+1,regs[i])==0)
      {
          *success=true;
    	  return cpu.gpr[i];
      }
    }else{
      if(strcmp(s,regs[i])==0)
      {
          *success=true;
    	  return cpu.gpr[i];
      }
    }
  }
  *success=false;  
  return -1;
}
