#include <stdio.h>
#include "avl.h"
#include "rbt.h"
#include "compare_trees.h"

int main()
{
    AVLTree *avl_tree = create_avl_tree();
    if (!avl_tree)
    {
        printf("Falha ao criar AVL Tree\n");
        return 1;
    }

    RedBlackTree *rbt_tree = create_rbt_tree(9999);
    if (!rbt_tree)
    {
        printf("Falha ao criar Red-Black Tree\n");
        return 1;
    }

    for (int i = 0; i < 10; i++)
    {
        rbt_tree->rbt_insert(rbt_tree, i);
        avl_tree->root = avl_tree->avl_insert(avl_tree, avl_tree->root, i);
    }

    printf("----- AVL Tree -----\n");
    printf("AVL Root: %d\n", avl_tree->root->key);
    avl_tree->avl_print_tree(avl_tree);
    printf("Total AVL Rotations(Left/Right): %d\n", avl_tree->total_rotations);

    printf("\n----- Red-Black Tree -----\n");
    printf("RBT Root: %d\n", rbt_tree->root->key);
    rbt_tree->rbt_print_tree(rbt_tree);
    printf("Total RBT Rotations(Left/Right): %d\n", rbt_tree->total_rotations);

    compare_trees(avl_tree, rbt_tree);

    return 0;
}
