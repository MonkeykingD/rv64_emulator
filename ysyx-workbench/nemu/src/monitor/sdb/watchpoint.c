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

#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char * expr;
  word_t oldval;
  word_t newval;

  /* TODO: Add more members if necessary */

} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp(){//Take the node from the head
  WP *tmp=free_;
  WP *last=NULL;
  if(tmp==NULL)
  {
    panic("There are no watchpoints available!!");
  }else if(tmp->next==NULL)
  {
    last=tmp;
    free_=NULL;
  }
  else{
    last=tmp;
    free_=tmp->next;
    last->next=NULL;
  }
  tmp=head;
  if(head==NULL)
  {
    head=last;
  }else{
    while(tmp->next){
      tmp=tmp->next;
    }
    tmp->next=last;
  }
  return last;
}
void free_wp(int No){
  WP *tmp=head;
  WP *f=NULL;
  if(tmp==NULL){
    panic("No watchpoints are working");
  }  
  if(head->NO==No){
    f=head;
    head=head->next;
  }else{  
    while(tmp->next!=NULL&&tmp->next->NO!=No){
      tmp=tmp->next;
    }
    if(tmp->next==NULL){
     printf("No watchdog found for that number\n");
     return;
    }else{
     f=tmp->next;
     tmp->next=tmp->next->next;
    }
  }
  printf("Watchpoint %d deleted\n",f->NO);
  free(f->expr);
  tmp=free_;
  if(tmp==NULL)
  {
    f->next=NULL;
    free_=f;
  }else if(tmp->next==NULL)
  {
    f->next=NULL;
    tmp->next=f; 
  }
  else{
    while(tmp->next){
      tmp=tmp->next;
    }
    f->next=NULL;
    tmp->next=f;
  }  
}
void add_wp(char * e){
    bool sa=false;
    bool *s=&sa;
    word_t val=0;
  //printf("expr si %s",w_args);
    val=expr(e,s);
   // printf("val is %lu\n",val);
    if(*s){
      WP *w=new_wp();
      w->expr=strdup(e);
      w->oldval=val;
      w->newval=val;
      printf("Set watchpoint %d\n",w->NO);
      printf("expr      =%s\n",w->expr); 
      printf("old value =0x%lx\n",w->oldval); 
    }
}
void displaywp(){
  WP *tmp=head;
  printf("NO\tExpr\t\tOld Value\n");
  while(tmp){
    printf("%d\t%s\t\t",tmp->NO,tmp->expr);
    printf(FMT_WORD,tmp->oldval);
    printf("\n");
    tmp=tmp->next;
  }
}
void scan(vaddr_t pc){
  WP *tmp=head;
  bool sa=false;
  bool *s=&sa;
  while(tmp){
    tmp->newval=expr(tmp->expr,s);
    if(tmp->newval!=tmp->oldval){
      nemu_state.state=NEMU_STOP;
      printf("Hit watchpoint %d at address ",tmp->NO);  
      printf(FMT_WORD,pc);
      printf("\n");
      printf("expr      =%s\n",tmp->expr); 
      printf("old value =0x%lx\n",tmp->oldval);  
      printf("new value =0x%lx\n",tmp->newval);      
      printf("program paused\n");
      tmp->oldval=tmp->newval;
      return;
    }
    tmp=tmp->next;
  }
  return;
}
