//
// Created by ryousuke kaga on 2023/10/03.
//

#include "test.h"
#include "test_list.h"
#include "test_htable.h"
#include "test_stack.h"
#include "test_queue.h"
#include "test_tree.h"
#include "test_binary_search.h"


MunitTest tests[] = {
        LIST_TESTS,
        HTABLE_TESTS,
        STACK_TESTS,
        QUEUE_TESTS,
        TREE_TESTS,
        BINARY_SEARCH_TESTS
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