#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include "../Headers/bstack.h"
#include <string.h>
#include <ctype.h>

BStack bstack_new(){
    BStack  bs = {NULL, 0};
    return bs;
}

uint32_t bstack_length(const BStack *bstack){
    assert(bstack != NULL);
    return bstack->length;
}

static Node* _get_new_node_(STACK_CONTENT_TYPE val){
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->data = val;
    newnode->prev = NULL;

    return newnode;
}

BStack* bstack_push(BStack *bstack, STACK_CONTENT_TYPE val){
    assert(bstack != NULL);
    Node *newnode = _get_new_node_(val);

    if(bstack->top == NULL) {
        bstack->top = newnode;
    } else {
        newnode->prev = bstack->top;
        bstack->top = newnode;
    }
    ++bstack->length;

    return bstack;
}

BStack* bstack_pop(BStack *bstack, BstackResult *res){
    assert(bstack != NULL);
    Node *cur;

    if(bstack->top != NULL && bstack->length > 0){
        res->data = bstack->top->data;
        bstack->top = bstack->top->prev;
    }
    --bstack->length;
    return bstack;
}


uint8_t bstack_check_expression(BStack *bstack, char *exp){
  BstackResult res;
  
  for(int i = 0; i < strlen(exp); i++){
       if(exp[i] == '[' ||  exp[i] == ']'){
          if(exp[i] == '['){
             bstack = bstack_push(bstack, exp[i]);
          } else {
             bstack = bstack_pop(bstack, &res);
             if (res.data != '['){
              return 0;
           }

       }
    }

      if(exp[i] == '(' || exp[i] == ')'){
          if(exp[i] == '('){
             bstack = bstack_push(bstack, exp[i]);
          } else {
             bstack = bstack_pop(bstack, &res);
             if (res.data != '('){
              return 0;
          }

       }
    }

     if(exp[i] == '{' || exp[i] == '}'){
          if(exp[i] == '{'){
             bstack = bstack_push(bstack, exp[i]);
          } else {
             bstack = bstack_pop(bstack, &res);
             if (res.data != '{'){
              return 0;
          }
       }
    }
    res.data = '\n';
  }
  
  return 1;

}

char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}
	

int16_t bstack_postfix_expression(BStack *bstack, char *postfix_exp){
    BstackResult res;
    int val;

    for(int i =0; i < strlen(postfix_exp); i++){
        if(isdigit(postfix_exp[i])){
            bstack = bstack_push(bstack, postfix_exp[i] - '0');
      } else if(postfix_exp[i] == '+' || postfix_exp[i] == '-' || postfix_exp[i] == '*' || postfix_exp[i] == '/'){
            bstack = bstack_pop(bstack, &res);
            int val1 = res.data;

            bstack = bstack_pop(bstack, &res);
            int val2 = res.data; 

            switch (postfix_exp[i]) 
            { 
            case '+':  val = val2 + val1; 
                       bstack = bstack_push(bstack, val); break; 
            case '-':  val = val2 - val1;
                       bstack = bstack_push(bstack, val); break; 
            case '*':  val = val2 * val1;
                       bstack = bstack_push(bstack, val); break; 
            case '/':  val = val2 / val1;
                       bstack = bstack_push(bstack, val); break; 
            } 
            if(bstack_length(bstack) != 1){
            res.data = '\n'; 
            }
      }
   }

   bstack = bstack_pop(bstack, &res);
   return res.data;
}
