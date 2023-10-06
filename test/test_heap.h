//
// Created by ryousuke kaga on 2023/10/06.
//

#ifndef MYALGORITHMS_TEST_HEAP_H
#define MYALGORITHMS_TEST_HEAP_H

#include "test.h"

TEST(test_heap) {
    Heap heap;
    heap_init(&heap, int_cmp, NULL);

    int xs[] = {1, 4, 6,45, 3};
    int sorted[] = {45, 6, 4, 3, 1};

    for(int i=0; i < 5; i++) {
        heap_insert(&heap, &xs[i]);
    }

    int* temp;
    for(int i=0; i < 5; i++) {
        heap_extract(&heap, (void**)&temp);
        munit_assert(*temp == sorted[i]);
    }

    return MUNIT_OK;
}

#define HEAP_TESTS \
    {              \
        "btree_heap", \
        test_heap, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }

#endif //MYALGORITHMS_TEST_HEAP_H
