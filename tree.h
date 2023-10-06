//
// Created by ryousuke kaga on 2023/10/06.
//

#ifndef MYALGORITHMS_TREE_H
#define MYALGORITHMS_TREE_H

#include <stdlib.h>
#include <string.h>

typedef struct BTreeNode_ {
    void* data;
    struct BTreeNode_* left;
    struct BTreeNode_* right;
} BTreeNode;

typedef struct BTree_ {
    int size;
    int (*compare)(const void* key1, const void* key2);
    void (*destroy)(void* data);
    BTreeNode* root;
} BTree;

void btree_init(BTree* tree, void (*destroy)(void* data));
void btree_destroy(BTree* tree);
int btree_ins_left(BTree* tree, BTreeNode* node, const void* data);
int btree_ins_right(BTree* tree, BTreeNode* node, const void* data);
void btree_rem_left(BTree* tree, BTreeNode* node);
void btree_rem_right(BTree* tree, BTreeNode* node);
int btree_merge(BTree* merge, BTree* left, BTree* right, const void* data);


#endif //MYALGORITHMS_TREE_H
