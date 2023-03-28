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

#ifndef __ISA_RISCV64_H__
#define __ISA_RISCV64_H__

#include <common.h>
#define MSTATUS   (0x300)
#define MTVEC     (0x305)
#define MEPC      (0x341)
#define MCAUSE    (0x342)
typedef struct {
  word_t gpr[32];
  vaddr_t pc;
  word_t csr[4];  
} riscv64_CPU_state;

// decode
typedef struct {
  union {
    uint32_t val;
  } inst;
} riscv64_ISADecodeInfo;
static inline int transform_csr_idx(int idx) {
  if(idx==MSTATUS){idx=0;}
  if(idx==MTVEC){idx=1;}
  if(idx==MEPC){idx=2;}
  if(idx==MCAUSE){idx=3;}
  return idx;
}
#define csr(idx) (cpu.csr[transform_csr_idx(idx)])
#define isa_mmu_check(vaddr, len, type) (MMU_DIRECT)

#endif
