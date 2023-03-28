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

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include <memory/vaddr.h>

enum {
  TK_NOTYPE = 256, TK_EQ=122,TK_NEQ=123,TK_DNUMBER=48,TK_HNUMBER=49,TK_REGISTER=50,TK_AND=51,DEREF=52,TK_NEG=53

  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal
  {"0[xX][0-9a-fA-F]+",TK_HNUMBER}, //16number
  {"[0-9]+",TK_DNUMBER}, // 10number
  {"\\-", '-'},         // minus
  {"\\/", '/'},		//division
  {"\\*", '*'},		//multiplication 
  {"\\(", '('},		//left bracket
  {"\\)", ')'},		//right bracket
  {"\\$[a-zA-z]{0,2}[0-9]*", TK_REGISTER},//REGISTER
  {"!=", TK_NEQ},//notequal
  {"\\&{2}", TK_AND}, //and

  
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

typedef struct mainop {
  int position;
  int type;
} Mainop;

static Token tokens[1024] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;
  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          case '+':case '-': case '*':case '/': case '(':case ')':
          	    tokens[nr_token].type = rules[i].token_type;
          	    tokens[nr_token++].str[0]=substr_start[0];
          	    break;
          case TK_NOTYPE:break;
   	  case TK_HNUMBER:case TK_DNUMBER:case TK_REGISTER:case TK_EQ:case TK_NEQ:case TK_AND:
 	  for(int i=0;i<substr_len;i++)
	    {
		tokens[nr_token].str[i]=substr_start[i];    //从第start+i个元素开始向数组内赋值
	    }
   	  tokens[nr_token++].type=rules[i].token_type;
   	  break;
   	  /*case '-':tokens[j].type = rules[j].token_type;
          	    j++;break;
   	  case '*':tokens[j].type = rules[j].token_type;
          	    j++;break;
   	  case '/':tokens[j].type = rules[j].token_type;
          	    j++;break;
   	  case '(':tokens[j].type = rules[j].token_type;
          	    j++;break;
   	  case ')':tokens[j].type = rules[j].token_type;
          	    j++;break;*/
          //default: TODO();
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  return true;
}

bool check_parentheses(int p, int q, int *state){
  if(tokens[p].type=='('&&tokens[q].type==')')
  {
    int top =0;
    for(int i=p;i<=q;i++)
    {
      if(top<0)
      {
        *state=2;
        return false;
      }
      if(tokens[i].type=='(')
      {
      	top+=1;
      }else if(tokens[i].type==')')
      {
        top-=1;
      }
      if(top==0&&i!=q){
        *state=3;
      }	      
      if(i==q)
      {
        if(top==0){
          if(*state==3){
            return false;
          }else{
            *state=0;
            return true;
          }
        }else{
          *state=2;
          return false;
        }
      }
    }
  }
  *state=1;
  return false;

}
int Lookfor_mainop(int p,int q){
    int index=-1;
    for(int i=p;i<=q;i++)
    {

      if(tokens[i].type==TK_DNUMBER||tokens[i].type==TK_HNUMBER)
      {
      	continue;
      }
      if(tokens[i].type=='('){
	      int top=0;
	      for(int j=i;j<=q;j++){
		//if(top<0)
		//{assert(0);}	
	      	if(tokens[j].type=='(')
	      	{
	      		top+=1;
	      	}else if(tokens[j].type==')')
	      	{
			top-=1;
	      	}
	      	if(top==0&&j!=q)
	      	{
	      		i=j+1;
	      		break;
	      	}
		if(top==0&&j==q)
	      	{
	      		i=j;
	      		break;
	      	}
	      }
      }//else if(tokens[i].type==')'){
        //assert(0);
      //}
        switch (tokens[i].type) {
          case '*':case '/':
            if(tokens[index].type!='+'&&tokens[index].type!='-'&&tokens[index].type!=TK_AND&&tokens[index].type!=TK_NEQ&&tokens[index].type!=TK_EQ)
            {
              index=i;
            }
            break;
          case '+':case '-': 
            if(tokens[index].type!=TK_AND&&tokens[index].type!=TK_NEQ&&tokens[index].type!=TK_EQ)
            {
              index=i;
            }
            break;
          case TK_NEQ:case TK_EQ:
            if(tokens[index].type!=TK_AND)
            {
              index=i;
            }
            break;   
          case TK_AND:
            index=i;
            break;              
      }
    
    }
    return index;
}

/*
static unsigned int atoui(const char *str);

unsigned int atoui(const char *str)
{
    unsigned int result = 0, i = 0;
    const char *tmp = NULL;
    tmp = str+i;
    while (*tmp)
    {
        result = result * 10 + *tmp - '0';
        tmp++;
    }

    return result;
}*/

word_t eval(int p,int q) {
  int state=0;//0:true 
  	      //1:false, the whole expression is not surrounded by a matched pair of parentheses 
  	      //2:false, bad expression
  	      //3:false, the leftmost '(' and the rightmost ')' are not matched
  if (p > q) {
    /* Bad expression */
    panic("This is not a legal expression");
  }
  else if (p == q) {                            
    /* Single token.
     * For now this token should be a number.
     * Return the value of the number.
     */
     if(tokens[p].type==TK_REGISTER)
     {
       bool state=false;
       word_t ans;
       ans=isa_reg_str2val(tokens[p].str,&state);
       if(state)
       {
         return ans;
       }else{
         panic("Dont find this register \n");

       }
     }
     else if(tokens[p].type==TK_NEG){
       uint64_t neg = 0;
       sscanf(tokens[p].str, "%lu", &neg);
       return neg;
     }else if(tokens[p].type==DEREF){
       word_t result;
       sscanf(tokens[p].str+1, "%lx", &result);
       result = vaddr_read(result, 8);
       return result; 
     }
     else{
       uint64_t nValude = 0;
       (tokens[p].type==TK_DNUMBER)?sscanf(tokens[p].str, "%lu", &nValude):sscanf(tokens[p].str, "%lx", &nValude);
       return nValude;
     }
  }
  else if (check_parentheses(p, q, &state) == true) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */
    return eval(p + 1, q - 1);
  }
  else {
    if(state==2)
    {
      panic("This is not a legal expression\n");
    }
    int index;
    index = Lookfor_mainop(p,q);
    //the position of 主运算符 in the token expression;
    uint64_t val1 = eval(p, index - 1);
    uint64_t val2 = eval(index + 1, q);
    switch (tokens[index].type) {
      case '+': return val1 + val2;break;
      case '-': return val1 - val2;break;/* ... */
      case '*':return val1 * val2;break;/* ... */
      case '/': return val1 / val2;break;/* ... */
      case TK_EQ: return val1==val2;break;
      case TK_NEQ: return val1!=val2;break;
      case TK_AND: return val1&&val2;break;
     // default: assert(0);
    }
  }
  return 1;
}
word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
    int p=0;
    int q=nr_token-1;

  /* TODO: Insert codes to evaluate the expression. */
 // printf("zhendeyun%u   %u",,-1);
	//eval(p,q);
  for(int i = 0 ;i<nr_token;i++) {
    if(tokens[i].type=='*'&&(i==0||(tokens[i-1].type!=TK_DNUMBER&&tokens[i-1].type!=')'&&tokens[i-1].type!=TK_HNUMBER&&tokens[i-1].type!=TK_REGISTER)))
    {
      tokens[i].type = DEREF;
      strcat(tokens[i].str,tokens[i+1].str);
      for(int j=i+1;j<nr_token;j++)
      {
        tokens[j]=tokens[j+1];
      }
      q--;
   //   strcat(tokens[i].str,tokens[i+1].str);
   //   q--;
    }
    if(tokens[i].type=='-'&&(i==0||(tokens[i-1].type!=TK_DNUMBER&&tokens[i-1].type!=')'&&tokens[i-1].type!=TK_HNUMBER&&tokens[i-1].type!=TK_REGISTER)))
    {
      tokens[i].type = TK_NEG;
      strcat(tokens[i].str,tokens[i+1].str);
      for(int j=i+1;j<nr_token;j++)
      {
        tokens[j]=tokens[j+1];
      }
      q--;
   //   strcat(tokens[i].str,tokens[i+1].str);
   //   q--;
    }
  }
  *success =true;
  return eval(p,q);
}
