//
// Created by ryousuke kaga on 2023/10/06.
//

#include "binary_search.h"

static void destroy_left(BSTree* tree, BTreeNode* node);
static void destroy_right(BSTree* tree, BTreeNode* node);

void rotate_left(BTreeNode** node) {
    BTreeNode *left, *grandchild;

    left = (*node)->left;

    if(bstree_factor(left) == AVL_LEFT_HEAVY) {
        (*node)->left = left->right;
        left->right = *node;
        bstree_factor(*node) = AVL_BALANCED;
        bstree_factor(left) = AVL_BALANCED;
        *node = left;
    } else {
        grandchild = left->right;
        left->right = grandchild->left;
        grandchild->left = left;
        (*node)->left = grandchild->right;
        grandchild->right = *node;

        switch(bstree_factor(grandchild)) {
            case AVL_LEFT_HEAVY:
                bstree_factor(*node) = AVL_RIGHT_HEAVY;
                bstree_factor(left) = AVL_BALANCED;
                break;
            case AVL_BALANCED:
                bstree_factor(*node) = AVL_BALANCED;
                bstree_factor(left) = AVL_BALANCED;
                break;
            case AVL_RIGHT_HEAVY:
                bstree_factor(*node) = AVL_BALANCED;
                bstree_factor(left) = AVL_LEFT_HEAVY;
                break;
        }

        bstree_factor(grandchild) = AVL_BALANCED;
        *node = grandchild;
    }
}

void rotate_right(BTreeNode** node) {
    BTreeNode *right, *grandchild;

   right = (*node)->right;

   if(bstree_factor(right) == AVL_RIGHT_HEAVY) {
       (*node)->right = right->left;
       right->left = *node;
       bstree_factor(*node) = AVL_BALANCED;
       bstree_factor(right) = AVL_BALANCED;
       *node = right;
   } else {
       grandchild = right->left;
       right->left = grandchild->right;
       grandchild->right = right;
       (*node)->right = grandchild->left;
       grandchild->left = *node;

       switch(bstree_factor(grandchild)) {
           case AVL_LEFT_HEAVY:
               bstree_factor(*node) = AVL_BALANCED;
               bstree_factor(right) = AVL_RIGHT_HEAVY;
               break;
           case AVL_BALANCED:
               bstree_factor(*node) = AVL_BALANCED;
               bstree_factor(right) = AVL_BALANCED;
               break;
           case AVL_RIGHT_HEAVY:
               bstree_factor(*node) = AVL_LEFT_HEAVY;
               bstree_factor(right) = AVL_BALANCED;
               break;
       }

       bstree_factor(grandchild) = AVL_BALANCED;
       *node = grandchild;
   }
}

int int_cmp(const void* key1, const void* key2) {
    return *(int*)(key1) - *(int*)(key2);
}

static void destroy_left(BSTree* tree, BTreeNode* node) {
    BTreeNode** position;
    if(tree->size == 0)
        return;

    if(node == NULL)
        position = &tree->root;
    else
        position = &node->left;

    if(*position != NULL) {
        destroy_left(tree, *position);
        destroy_right(tree, *position);

        if(tree->destroy != NULL) {
            tree->destroy(bstree_data(*position));
        }


        free((*position)->data);
        free(*position);
        *position = NULL;
        tree->size--;
    }
}

static void destroy_right(BSTree* tree, BTreeNode* node) {
    BTreeNode** position;
    if(tree->size == 0)
        return;

    if(node == NULL)
        position = &tree->root;
    else
        position = &node->right;

    if(*position != NULL) {
        destroy_left(tree, *position);
        destroy_right(tree, *position);

        if(tree->destroy != NULL) {
            tree->destroy(bstree_data(*position));
        }

        free((*position)->data);
        free(*position);
        *position = NULL;
        tree->size--;
    }
}

static int insert(BSTree* tree, BTreeNode** node, const void* data, int* balanced) {
    AvlNode *avl_data;
    int cmpval, retval;

    if((avl_data = (AvlNode*)malloc(sizeof(AvlNode))) == NULL)
        return -1;

    avl_data->factor = AVL_BALANCED;
    avl_data->hidden = 0;
    avl_data->data = (void*)data;

    if(*node == NULL) {
        return btree_ins_left(tree, *node, avl_data); // just insert into the node
    } else {
        cmpval = tree->compare(data, bstree_data(*node));

        if(cmpval < 0) {
            if((*node)->left == NULL) {
                if(btree_ins_left(tree, *node, avl_data) != 0)
                    return -1;

                *balanced = 0;
            } else if((retval = insert(tree, &(*node)->left, data, balanced)))
                return retval; // if insertion failed


            if(!(*balanced)) { // if not balanced, balance
                switch(bstree_factor(*node)) {
                    case AVL_LEFT_HEAVY:
                        rotate_left(node);
                        *balanced = 1;
                        break;
                    case AVL_BALANCED:
                        bstree_factor(*node) = AVL_LEFT_HEAVY;
                        break;
                    case AVL_RIGHT_HEAVY:
                        bstree_factor(*node) = AVL_BALANCED;
                        *balanced = 1;
                        break;
                }
            }
        } else if(cmpval > 0) {
            if((*node)->right == NULL) {
                if(btree_ins_right(tree, *node, avl_data) != 0)
                    return -1;

                *balanced = 0;
            } else if((retval = insert(tree, &(*node)->right, data, balanced)))
                return retval; // if insertion failed


            if(!(*balanced)) { // if not balanced, balance
                switch(bstree_factor(*node)) {
                    case AVL_LEFT_HEAVY:
                        bstree_factor(*node) = AVL_BALANCED;
                        *balanced = 1;
                        break;
                    case AVL_BALANCED:
                        bstree_factor(*node) = AVL_RIGHT_HEAVY;
                        break;
                    case AVL_RIGHT_HEAVY:
                        rotate_right(node);
                        *balanced = 1;
                        break;
                }
            }
        } else { // if cmp == 0 replace
            if(!bstree_hidden(*node))
                return 1;
            if(tree->destroy != NULL)
                tree->destroy(bstree_data(*node));

            bstree_data(*node) = (void*)data;
            bstree_hidden(*node) = 0;
        }
    }

    return 0;
}

static int hide(BSTree* tree, BTreeNode* node, const void* data) {
    int cmpval, retval;

    if(node == NULL)
        return -1;

    cmpval = tree->compare(data, bstree_data(node));

    if(cmpval < 0)
        retval = hide(tree, node->left, data);
    else if(cmpval > 0)
        retval = hide(tree, node->right, data);
    else {
        bstree_hidden(node) = 1;
        retval = 0;
    }

    return retval;
}

static int lookup(BSTree* tree, BTreeNode* node, void** data) {
    int cmpval, retval;

    if(node == NULL)
        return -1;

    cmpval = tree->compare(data, bstree_data(node));

    if(cmpval < 0)
        retval = lookup(tree, node->left, data);
    else if(cmpval > 0)
        retval = lookup(tree, node->right, data);
    else {
        if(!bstree_hidden(node)) {
            *data = bstree_data(node);
            retval = 0;
        } else {
            return -1;
        }
    }

    return retval;
}

void bstree_init(BSTree* tree, int (*compare)(const void* key1, const void* key2), void (*destory)(void* data)) {
    btree_init(tree, destory);
    tree->compare = compare;
}

void bstree_destroy(BSTree* tree) {
    destroy_left(tree, NULL);
    memset(tree, 0, sizeof(BSTree));
}

int bstree_insert(BSTree* tree, const void* data) {
    int balanced = 0;
    return insert(tree, &tree->root, data, &balanced);
}

int bstree_remove(BSTree* tree, const void* data) {
    return hide(tree, tree->root, data);
}

int bstree_lookup(BSTree* tree, void** data) {
    return lookup(tree, tree->root, data);
}