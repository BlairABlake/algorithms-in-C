//
// Created by ryousuke kaga on 2023/10/06.
//

#ifndef MYALGORITHMS_TEST_STACK_H
#define MYALGORITHMS_TEST_STACK_H

#include "test.h"

TEST(test_stack_LIFO) {
    Stack stack;
    stack_init(&stack, NULL);

    int xs[] = {1, 2, 3, 4, 5};

    for(int i=0; i < 5; i++) {
        stack_push(&stack, &xs[i]);
    }

    int* tmp;
    for(int i=0; i < 5; i++) {
        stack_pop(&stack, (void **)&tmp);
        munit_assert(tmp == &xs[4-i]);
    }

    return MUNIT_OK;
}

#define STACK_TESTS \
    {              \
        "stack_LIFO", \
        test_stack_LIFO, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }

#endif //MYALGORITHMS_TEST_STACK_H
