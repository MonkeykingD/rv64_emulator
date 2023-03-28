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

#include <common.h>

extern uint64_t g_nr_guest_inst;
RingBuffer rb;
Functable ffunc[100];
FILE *log_fp = NULL;
FILE *elf_fp = NULL;

void init(RingBuffer *rb) {
    rb->p=0;
    rb->head=0;
    rb->flag=false;
}
void printrb(RingBuffer *rb){
  int k;
  if(rb->p==0)
  {
    k=BUFFER_SIZE;
  }else{
    k=rb->p-1;
  }
  printf("The ring buffer stores the most recent BUFFER_SIZE instructions\n");  
  for(int i=rb->head;i!=k; i = (i + 1) % BUFFER_SIZE)
  {
    printf("\t%s\n",rb->buffer[i%10]);    
  }
  printf("-->\t%s\n",rb->buffer[k]);   
}
void push(RingBuffer *rb, char *str) {
    strcpy(rb->buffer[rb->p], str);
    if(rb->p ==rb->head){
      if(rb->flag==false)
      {
        rb->flag=true;
      }else{
        rb->head=(rb->head + 1) % BUFFER_SIZE;
      }
    }
    rb->p = (rb->p + 1) % BUFFER_SIZE;
}//itrace

#ifdef CONFIG_MTRACE   
FILE *mtrace_fp = NULL;
void init_mtrace() {
    // write header to file
    mtrace_fp= fopen("mtrace.log", "w");
    if (mtrace_fp == NULL) {
        fprintf(stderr, "Error: failed to open file 'mtrace.log' for writing\n");
        return ;
    }
    fprintf(mtrace_fp, "addr\t\tsize\ttype\n");
}

void add_mtrace(FILE* fp, paddr_t addr, int size, int type) {
    // write entry to file
    fprintf(fp, "0x%x\t%d\t%s\n", addr, size, type == 0 ? "read" : "write");
}//mtrace
#endif    

void init_ftrace(const char *elf_file){
  if (elf_file == NULL)
  {
    printf("Not ELFfile!!\n");
  
  }else{
  FILE *fp = fopen(elf_file, "r");
  Assert(fp, "Can not open '%s'", elf_file);
  elf_fp = fp; 
  //elfheader-->section header-->Section Name String Table Section-->.symtab and .strtab
  Elf64_Ehdr hdr;
  fseek(elf_fp, 0, SEEK_SET);//the ELF header
  if(fread(&hdr, sizeof(Elf64_Ehdr), 1, elf_fp)){};  
  fseek(elf_fp, hdr.e_shoff, SEEK_SET);//the section header table
  int count = hdr.e_shnum;    //True when less than SHN_LORESERVE (0xff00).
  Elf64_Shdr *shdr= malloc(sizeof(Elf64_Shdr) * count);
  if(fread(shdr, hdr.e_shentsize, count, elf_fp)){};
  fseek(elf_fp, shdr[hdr.e_shstrndx].sh_offset, SEEK_SET);//the section name string table
  char *StringNameTable=malloc(shdr[hdr.e_shstrndx].sh_size);
  char *StringTable=NULL;
  Elf64_Sym *sym=NULL;
  int symflg=0,strtab=0;
  if(fread(StringNameTable, 1, shdr[hdr.e_shstrndx].sh_size, elf_fp)){}; 
  for(int i=0;i<count;i++){
    if(strcmp(".symtab",&StringNameTable[shdr[i].sh_name])==0){
      fseek(elf_fp, shdr[i].sh_offset, SEEK_SET);//the string table
      sym=malloc(shdr[i].sh_size);
      symflg=shdr[i].sh_size;
      if(fread(sym, sizeof(Elf64_Sym), symflg / sizeof(Elf64_Sym), elf_fp)){}; 
    }
    if(strcmp(".strtab",&StringNameTable[shdr[i].sh_name])==0){
      fseek(elf_fp, shdr[i].sh_offset, SEEK_SET);//the string table
      StringTable=malloc(shdr[i].sh_size);
      if(fread(StringTable,shdr[i].sh_size, 1, elf_fp)){}; 
      strtab=shdr[i].sh_size;
    }
    if(symflg&&strtab){
      break;
    }   
  }
  int times=0;
    for (int i = 0; i < symflg / sizeof(Elf64_Sym); i++) {
        if (sym[i].st_info == 18) {
            
            strcpy(ffunc[times].name,StringTable +sym[i].st_name);
            ffunc[times].addr=sym[i].st_value;
            ffunc[times++].size=sym[i].st_size;
        }
    }
    free(shdr);
    free(StringNameTable);
    free(sym);
    free(StringTable);
  }  
}
void init_log(const char *log_file) {
  log_fp = stdout;
  init(&rb);
#ifdef CONFIG_MTRACE  
  init_mtrace();
#endif   
  if (log_file != NULL) {
    FILE *fp = fopen(log_file, "w");
    Assert(fp, "Can not open '%s'", log_file);
    log_fp = fp;
  }
  Log("Log is written to %s", log_file ? log_file : "stdout");
}

bool log_enable() {
  return MUXDEF(CONFIG_TRACE, (g_nr_guest_inst >= CONFIG_TRACE_START) &&
         (g_nr_guest_inst <= CONFIG_TRACE_END), false);
}
