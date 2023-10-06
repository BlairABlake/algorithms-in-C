//
// Created by ryousuke kaga on 2023/10/06.
//

#ifndef MYALGORITHMS_TEST_BINARY_SEARCH_H
#define MYALGORITHMS_TEST_BINARY_SEARCH_H

#include "test.h"

TEST(test_bstree_insertion) {
    BSTree tree;
    bstree_init(&tree, int_cmp, NULL);
    int xs[] = {1, 2, 3, 4, 5, 6};
    for(int i=0; i < 6; i++) {
        munit_assert(bstree_insert(&tree, &xs[i]) == 0);
        munit_assert(tree.size == i + 1);
    }
    munit_assert(*(int*)bstree_data(tree.root) == 4);
    munit_assert(*(int*)bstree_data(tree.root->left) == 2);
    munit_assert(*(int*)bstree_data(tree.root->right) == 5);
    munit_assert(*(int*)bstree_data(tree.root->left->right) == 3);
    munit_assert(*(int*)bstree_data(tree.root->left->left) == 1);
    munit_assert(*(int*)bstree_data(tree.root->right->right) == 6);

    bstree_destroy(&tree);
    return MUNIT_OK;
}

#define BINARY_SEARCH_TESTS \
    {                \
        "bstree_insertion", \
        test_bstree_insertion, \
        NULL,        \
        NULL,        \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },

#endif //MYALGORITHMS_TEST_BINARY_SEARCH_H
