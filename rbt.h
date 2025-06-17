#ifndef RBT_H
#define RBT_H


typedef struct RBTNode
{
    int key;
    struct RBTNode *parent;
    struct RBTNode *left;
    struct RBTNode *right;
    int color;
    void(*print_color);
} RBTNode;

typedef struct RedBlackTree
{
    RBTNode *NIL;
    RBTNode *root;
    void (*rbt_print_tree)(struct RedBlackTree *);
    RBTNode *(*rbt_search)(struct RedBlackTree *, int);
    RBTNode *(*rbt_minimum)(struct RedBlackTree *, RBTNode *);
    void (*rbt_transplant)(struct RedBlackTree *, RBTNode *, RBTNode *);
    void (*rbt_delete_fixup)(struct RedBlackTree *, RBTNode *);
    void (*rbt_delete)(struct RedBlackTree *, int);
    void (*rbt_insert)(struct RedBlackTree *, int);
    void (*rbt_insert_fixup)(struct RedBlackTree *, RBTNode *);
    void (*rbt_right_rotate)(struct RedBlackTree *, RBTNode *);
    void (*rbt_left_rotate)(struct RedBlackTree *, RBTNode *);
    void (*rbt_free_tree)(struct RedBlackTree *); // <- nova função para liberar memória
    int total_rotations;

} RedBlackTree;

RedBlackTree *create_rbt_tree(int);

#endif
