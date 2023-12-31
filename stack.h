//
// Created by ryousuke kaga on 2023/10/06.
//

#ifndef MYALGORITHMS_STACK_H
#define MYALGORITHMS_STACK_H

#include "list.h"

typedef List Stack;

#define stack_init list_init
#define stack_destroy list_destroy
int stack_push(Stack* stack, const void* data);
int stack_pop(Stack* stack, void** data);
#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)
#define stack_size list_size

#endif //MYALGORITHMS_STACK_H
