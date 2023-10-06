//
// Created by ryousuke kaga on 2023/10/06.
//

#ifndef MYALGORITHMS_TEST_TREE_H
#define MYALGORITHMS_TEST_TREE_H

#include "test.h"

TEST(test_btree_instantiation) {
    BTree tree;
    btree_init(&tree, NULL);

    munit_assert(tree.size == 0);
    munit_assert(tree.root == NULL);
    munit_assert(tree.destroy == NULL);
}

TEST(test_btree_insertion_into_root_if_NULL) {
    BTree tree1;
    btree_init(&tree1, NULL);

    int data[] = {1, 2, 3};
    munit_assert(btree_ins_left(&tree1, NULL, &data[0]) == 0);
    munit_assert(tree1.root->data == &data[0]);

    BTree tree2;
    btree_init(&tree1, NULL);

    munit_assert(btree_ins_right(&tree2, NULL, &data[0]) == 0);
    munit_assert(tree2.root->data == &data[0]);
}

TEST(test_btree_insertion_fail_if_NULL) {
    BTree tree1;
    btree_init(&tree1, NULL);

    int data[] = {1, 2, 3};
    munit_assert(btree_ins_left(&tree1, NULL, &data[0]) == 0);
    munit_assert(btree_ins_left(&tree1, NULL, &data[1]) == -1);

    BTree tree2;
    btree_init(&tree2, NULL);

    munit_assert(btree_ins_right(&tree2, NULL, &data[0]) == 0);
    munit_assert(btree_ins_right(&tree2, NULL, &data[1]) == -1);
}

TEST(test_btree_insertion) {
    BTree tree1;
    btree_init(&tree1, NULL);

    int data[] = {1, 2, 3};
    munit_assert(btree_ins_left(&tree1, NULL, &data[0]) == 0);
    munit_assert(btree_ins_left(&tree1, tree1.root, &data[1]) == 0);
    munit_assert(tree1.root->left->data == &data[1]);

    BTree tree2;
    btree_init(&tree2, NULL);

    munit_assert(btree_ins_right(&tree2, NULL, &data[0]) == 0);
    munit_assert(btree_ins_right(&tree2, tree2.root, &data[1]) == 0);
    munit_assert(tree2.root->right->data == &data[1]);
}


TEST(test_btree_insertion_fail_if_occupied) {
    BTree tree1;
    btree_init(&tree1, NULL);

    int data[] = {1, 2, 3};
    munit_assert(btree_ins_left(&tree1, NULL, &data[0]) == 0);
    munit_assert(btree_ins_left(&tree1, tree1.root, &data[1]) == 0);
    munit_assert(btree_ins_left(&tree1, tree1.root, &data[2]) == -1);

    BTree tree2;
    btree_init(&tree2, NULL);

    munit_assert(btree_ins_right(&tree2, NULL, &data[0]) == 0);
    munit_assert(btree_ins_right(&tree2, tree2.root, &data[1]) == 0);
    munit_assert(btree_ins_right(&tree2, tree2.root, &data[2]) == -1);
}

TEST(test_btree_remove) {
    BTree tree1;
    btree_init(&tree1, NULL);

    int data[] = {1, 2, 3};
    munit_assert(btree_ins_left(&tree1, NULL, &data[0]) == 0);
    btree_rem_left(&tree1, tree1.root);
    munit_assert(tree1.root->left == NULL);

    BTree tree2;
    btree_init(&tree2, NULL);

    munit_assert(btree_ins_right(&tree2, NULL, &data[0]) == 0);
    btree_rem_left(&tree2, tree2.root);
    munit_assert(tree2.root->right == NULL);
}

#define TREE_TESTS \
    {              \
        "btree_instantiation", \
        test_btree_instantiation, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },             \
    {              \
        "btree_insertion_into_root_if_NULL", \
        test_btree_insertion_into_root_if_NULL, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },             \
    {              \
        "btree_insertion_fail_if_NULL", \
        test_btree_insertion_fail_if_NULL, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },             \
    {              \
        "btree_insertion", \
        test_btree_insertion, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },             \
    {              \
        "btree_remove", \
        test_btree_remove, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },             \
    {              \
        "btree_insertion_fail_if_occupied", \
        test_btree_insertion_fail_if_occupied, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }


#endif //MYALGORITHMS_TEST_TREE_H
