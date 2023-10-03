//
// Created by ryousuke kaga on 2023/10/03.
//

#include "test.h"
#include "test_list.h"
#include "test_htable.h"


MunitTest tests[] = {
        LIST_TESTS,
        HTABLE_TESTS
};

static const MunitSuite suite = {
        "/tests/",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
};

int main(int argc, const char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}