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
word_t expr(char *, bool *);
void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();
void expr_test(void) {
  bool ret;
  uint32_t testinput, testoutput;
  FILE* fp = fopen("/home/mkdai/ysyx-workbench/nemu/tools/gen-expr/input", "r");
  if (fp == NULL) {
    printf("Fail to open file!\n");
    exit(0);  //退出程序（结束程序）
  }
  char buf[1024];
  /* 读取每一行
   * 换行键被坑了
   * fgets函数，会默认添加换行\n,导致字符串结尾是 \n\0"
   */
       int right=0,fail=0;
  while (fgets(buf, sizeof(buf), fp) != NULL) {

    char* find = strchr(buf, '\n');  //找出data中的"\n"
    if (find)
      *find = '\0';   //替换
    /* 参考nemu读取命令的代码 */
    char* cmd = strtok(buf, " ");
    char* args = cmd + strlen(cmd) + 1;
   // printf("cmd=%s\n", cmd);
   // printf("args=%s\n", args);

    testinput = (uint32_t)atoi(cmd);//默认结果
    testoutput = expr(args, &ret);//输出结果
    if(testinput == testoutput)
    {right++;}
    else{
     printf("mathine compute digital:%u,biaodashi is %s,expr compute is %u",testinput,args,testoutput);
    fail++;}
    //printf("input:%u,output:%u\n", testinput, testoutput);
  }
  printf("right:%d,fail:%d",right,fail);
  fclose(fp);
}
int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif	
	//expr_test();
 // new_wp();
//printf("%lu",expr("1+*0x80000000",false));
  /* Start engine. */
  engine_start();
    
  return is_exit_status_bad();
}
