//
// Created by ryousuke kaga on 2023/10/04.
//

#ifndef MYALGORITHMS_TEST_HTABLE_H
#define MYALGORITHMS_TEST_HTABLE_H

#include "test.h"

TEST(test_htable_insert) {
    Htbl table;
    htbl_init(&table, 100, (int (*)(const void *)) hashpjw, char_match, NULL);


    char* s1 = "sdfajef";
    char* s2 = "fsaf";

    htbl_insert(&table, s1);
    munit_assert(htbl_lookup(&table, (void*)&s1) == 0);
    munit_assert(htbl_lookup(&table, (void*)&s2) != 0);

    htbl_insert(&table, s2);
    munit_assert(htbl_lookup(&table, (void*)&s2) == 0);

    return MUNIT_OK;
}


#define HTABLE_TESTS \
    {                \
        "htable_insert", \
        test_htable_insert, \
        NULL,        \
        NULL,        \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }


#endif //MYALGORITHMS_TEST_HTABLE_H
