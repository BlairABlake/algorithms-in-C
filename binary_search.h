//
// Created by ryousuke kaga on 2023/10/06.
//

#ifndef MYALGORITHMS_BINARY_SEARCH_H
#define MYALGORITHMS_BINARY_SEARCH_H

#include "tree.h"

#define AVL_LEFT_HEAVY 1
#define AVL_BALANCED 0
#define AVL_RIGHT_HEAVY -1

typedef struct AvlNode_ {
    void *data;
    int hidden;
    int factor;
} AvlNode;

typedef BTree BSTree;

#define bstree_factor(node) ((AvlNode*)(node)->data)->factor
#define bstree_data(node) ((AvlNode*)(node)->data)->data
#define bstree_hidden(node) ((AvlNode*)(node)->data)->hidden


void bstree_init(BSTree* tree, int (*compare)(const void* key1, const void* key2), void (*destory)(void* data));
void bstree_destroy(BSTree* tree);
int bstree_insert(BSTree* tree, const void* data);
int bstree_remove(BSTree* tree, const void* data);
int bstree_lookup(BSTree* tree, void** data);

int int_cmp(const void* key1, const void* key2);

void rotate_left(BTreeNode** node);
void rotate_right(BTreeNode** node);



#endif //MYALGORITHMS_BINARY_SEARCH_H
