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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
//#include <errno.h>
int len;
// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";
uint32_t choose(uint32_t n){
  return rand() % n;
}
static void gen_num(){
  uint32_t num=choose(4);
  len += sprintf(buf + len, "%u", num);
}
static void gen_rand_op(){
  static char ops[] = "+-*/";
  buf[len ++] = ops[choose(4)];
    
}
static void gen(char c){
  buf[len ++] =c;
}
static void gen_space(){
  int i=choose(2);
  while(i>0){
    buf[len ++] =' ';
    i--;
  }
}
static void gen_rand_expr() {
  uint32_t chose = choose(3);
  if (strlen(buf) > 20) {
    chose = 0;
  }  
    switch (chose) {
    case 0: gen_space;gen_num();gen_space; break;
    case 1: gen_space();gen('(');gen_space(); gen_rand_expr();gen_space(); gen(')');gen_space(); break;
    default: gen_rand_expr(); gen_rand_op(); gen_rand_expr(); break;
  }
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    memset(buf,'\0',len);
    len=0;
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -Werror  -o  /tmp/.expr");
    if (ret == 256) {
      i=i-1;
      continue;
    }
    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    fscanf(fp, "%d", &result);
    pclose(fp);
    //int  rv = pclose(fp);
    //if (136 == WEXITSTATUS(rv))
   // {
   // printf("chu cuo la ");
   // 	i=i-1;
//	continue;
  //  }
    printf("%u %s\n", result, buf);
    
  }
  return 0;
}
