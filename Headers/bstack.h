#include <stdint.h>
#include "../Headers/appconst.h"
#ifndef BSTACK_H_INCLUDED
#define BSTACK_H_INCLUDED

#ifndef STACK_CONTENT_TYPE
#define STACK_CONTENT_TYPE int32_t
#endif

typedef struct _node_ Node;

struct _node_{
    STACK_CONTENT_TYPE data;
    Node *prev;
};


typedef struct _bstack_ BStack;


struct _bstack_ {
    Node *top;
    uint32_t length;
};

typedef struct _bstack_result_ BstackResult;

struct _bstack_result_ {
    STACK_CONTENT_TYPE data;
    uint32_t status;
};

BStack bstack_new();
uint32_t bstack_length(const BStack *bstack);
BStack* bstack_push(BStack *bstack, STACK_CONTENT_TYPE val);
BStack* bstack_pop(BStack *bstack, BstackResult *res);
uint8_t bstack_check_expression(BStack *bstack, char *exp);
int16_t bstack_postfix_expression(BStack *bstack, char *postfix_exp);

#endif // BSTACK_H_INCLUDED
