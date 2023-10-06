//
// Created by ryousuke kaga on 2023/10/06.
//

#include "stack.h"

int stack_push(Stack* stack, const void* data) {
    return list_ins_next(stack, NULL, data); // NULL indicates the head
}

int stack_pop(Stack* stack, void** data) {
    return list_rem_next(stack, NULL, data); // NULL indicates the head
}