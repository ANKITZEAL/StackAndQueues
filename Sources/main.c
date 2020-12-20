#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../Headers/bstack.h"

//1. Check balancing of symbols (like ‘{‘, ‘(‘, ‘[‘ ) and their order using stack.
void test1(){
    BStack bs = bstack_new();
    BStack *bstack = &bs;
    BstackResult res;
  
   char exp[] = "[([a+b])+[c*d]{5}]";

   assert(bstack_check_expression(bstack, exp) == 1 && bstack_length(bstack) == 0);

}


//2. Evaluate postfix expression using stack.  Example: postfix fix expression is 6 5 2 3 + 8 * + 3 + *
void test2(){
    BStack bs = bstack_new();
    BStack *bstack = &bs;
    BstackResult res;
 
   char postfix_exp[] = "6 5 2 3 + 8 * + 3 + *";
   bstack_postfix_expression(bstack, postfix_exp);
   assert(bstack_postfix_expression(bstack, postfix_exp) == 288);

}


int main(){
    test1();
    test2();
    return 0;
}
