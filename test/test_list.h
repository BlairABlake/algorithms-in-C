//
// Created by ryousuke kaga on 2023/10/03.
//

#ifndef MYALGORITHMS_TEST_LIST_H
#define MYALGORITHMS_TEST_LIST_H

#include "test.h"

TEST(test_list_init) {
    List l;
    list_init(&l, free);
    munit_assert(l.size == 0);
    munit_assert(l.destroy == free);
    munit_assert(l.head == NULL);
    munit_assert(l.tail == NULL);

    return MUNIT_OK;
}

TEST(test_list_insert) {
    List l;
    list_init(&l, free);


    munit_assert(list_ins_next(&l, NULL, malloc(2)) == 0);
    munit_assert(l.size == 1);

    list_destroy(&l);

    return MUNIT_OK;
}

#define LIST_TESTS \
    {              \
        "list_init", \
        test_list_init, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },             \
    {              \
        "list_insert", \
        test_list_insert, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }

#endif //MYALGORITHMS_TEST_LIST_H
