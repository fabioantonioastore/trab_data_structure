#ifndef AVL_H
#define AVL_H


typedef struct AVLNode
{
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

typedef struct AVLTree
{
    AVLNode *root;
    int (*get_height)(AVLNode *);
    int (*get_balance_factor)(AVLNode *);
    AVLNode *(*get_min_node)(AVLNode *);
    AVLNode *(*avl_search)(struct AVLTree *, int);
    AVLNode *(*avl_insert)(struct AVLTree*, AVLNode *, int);
    AVLNode *(*avl_delete)(struct AVLTree*, AVLNode *, int);
    AVLNode *(*avl_right_rotate)(struct AVLTree*, AVLNode *);
    AVLNode *(*avl_left_rotate)(struct AVLTree*, AVLNode *);
    void (*print_search)(struct AVLTree *, int);
    void (*avl_print_tree)(struct AVLTree *);
    void (*avl_free_tree)(struct AVLTree *);
    int total_rotations;
} AVLTree;

AVLTree *create_avl_tree();

#endif
