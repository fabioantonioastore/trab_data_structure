#include <stdio.h>
#include <stdlib.h>
#include "rbt.h"
#include "queue.h"

#define RED 1
#define BLACK 0


void print_color(RBTNode *node)
{
    if (node->color == BLACK)
    {
        printf("Black\n");
    }
    else
    {
        printf("Red\n");
    }
}

RBTNode *create_rbt_node(int key)
{
    RBTNode *node = (RBTNode *)malloc(sizeof(RBTNode));
    node->key = key;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->print_color = print_color;
    return node;
}

// O(1)
void rbt_left_rotate(RedBlackTree *tree, RBTNode *node)
{
    tree->total_rotations += 1;
    RBTNode *right_node = node->right;
    node->right = right_node->left;

    if (right_node->left != tree->NIL)
    {
        right_node->left->parent = node;
    }

    right_node->parent = node->parent;

    if (!node->parent)
    {
        tree->root = right_node;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = right_node;
    }
    else
    {
        node->parent->right = right_node;
    }

    right_node->left = node;
    node->parent = right_node;
}

// O(1)
void rbt_right_rotate(RedBlackTree *tree, RBTNode *node)
{
    tree->total_rotations += 1;
    RBTNode *left_node = node->left;
    node->left = left_node->right;

    if (left_node->right != tree->NIL)
    {
        left_node->right->parent = node;
    }

    left_node->parent = node->parent;

    if (!node->parent)
    {
        tree->root = left_node;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = left_node;
    }
    else
    {
        node->parent->left = left_node;
    }

    left_node->right = node;
    node->parent = left_node;
}

// O(log n)
void rbt_insert_fixup(RedBlackTree *tree, RBTNode *z)
{
    while (z->parent && z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            RBTNode *y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rbt_left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbt_right_rotate(tree, z->parent->parent);
            }
        }
        else
        {
            RBTNode *y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rbt_right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbt_left_rotate(tree, z->parent->parent);
            }
        }
        if (z == tree->root)
        {
            break;
        }
    }
    tree->root->color = BLACK;
}

// O(log n)
void rbt_insert(RedBlackTree *tree, int key)
{
    RBTNode *z = create_rbt_node(key);
    z->left = tree->NIL;
    z->right = tree->NIL;

    RBTNode *y = NULL;
    RBTNode *x = tree->root;

    while (x != tree->NIL)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (!y)
    {
        tree->root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    rbt_insert_fixup(tree, z);
}

// O(log n)
RBTNode *rbt_search(RedBlackTree *tree, int key)
{
    RBTNode *node = tree->root;
    while (node != tree->NIL && key != node->key)
    {
        if (key < node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return node;
}

// O(log n)
RBTNode *rbt_minimum(RedBlackTree *tree, RBTNode *node)
{
    while (node != tree->NIL)
    {
        node = node->left;
    }
    return node;
}

// O(1)
void rbt_transplant(RedBlackTree *tree, RBTNode *u, RBTNode *v)
{
    if (!u->parent)
    {
        tree->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// O(log n)
void rbt_delete_fixup(RedBlackTree *tree, RBTNode *node)
{
    while (node != tree->root && node->color == BLACK)
    {
        if (node == node->parent->left)
        {
            RBTNode *w = node->parent->right;

            // Type 1
            if (w->color == RED)
            {
                w->color = BLACK;
                node->parent->color = RED;
                rbt_left_rotate(tree, node->parent);
                w = node->parent->right;
            }

            // Type 2
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                node = node->parent;
            }
            else
            {
                // Type 3
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rbt_right_rotate(tree, w);
                    w = node->parent->right;
                }
                // Type 4
                w->color = node->parent->color;
                node->parent->color = BLACK;
                w->right->color = BLACK;
                rbt_left_rotate(tree, node->parent);
                node = tree->root;
            }
        }
        else
        {
            RBTNode *w = node->parent->left;

            // Type 1
            if (w->color == RED)
            {
                w->color = BLACK;
                node->parent->color = RED;
                rbt_right_rotate(tree, node->parent);
                w = node->parent->left;
            }
            // Type 2
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                node = node->parent;
            }
            else
            {
                // Type 3
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbt_left_rotate(tree, w);
                    w = node->parent->left;
                }
                // Type 4
                w->color = node->parent->color;
                node->parent->color = BLACK;
                w->left->color = BLACK;
                rbt_right_rotate(tree, node->parent);
                node = tree->root;
            }
        }
    }
    node->color = BLACK;
}

// O(log n)
void rbt_delete(RedBlackTree *tree, int key)
{
    RBTNode *z = rbt_search(tree, key);

    if (z == tree->NIL)
    {
        printf("Key not found");
        return;
    }

    RBTNode *y = z;
    int y_orign_color = y->color;

    RBTNode *x = NULL;

    // Case 1
    if (z->left == tree->NIL)
    {
        x = z->right;
        rbt_transplant(tree, z, z->right);
    }
    // Case 2
    else if (z->right == tree->NIL)
    {
        x = z->left;
        rbt_transplant(tree, z, z->left);
    }
    // Case 3
    else
    {
        y = rbt_minimum(tree, z->right);
        y_orign_color = y->color;
        x = y->right;

        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rbt_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbt_transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_orign_color == BLACK)
    {
        rbt_delete_fixup(tree, x);
    }
}

void rbt_print_tree(RedBlackTree *tree)
{
    if (tree->root)
    {
        Queue *queue = create_queue();
        queue->enqueue(queue, tree->root);

        while (!queue->is_empty(queue))
        {
            RBTNode *node = queue->dequeue(queue);

            if (node->color == BLACK)
            {
                printf("Key: %d\t Color: Black\n", node->key);
            }
            else
            {
                printf("Key: %d\t Color: Red\n", node->key);
            }

            if (node->left && node->left != tree->NIL)
            {
                queue->enqueue(queue, node->left);
            }
            if (node->right && node->right != tree->NIL)
            {
                queue->enqueue(queue, node->right);
            }
        }
        free(queue);
    }
    else
    {
        printf("Tree is empty\n");
    }
}

// Função auxiliar para liberar os nós da árvore recursivamente
void rbt_free_nodes(RedBlackTree *tree, RBTNode *node)
{
    if (node == tree->NIL || node == NULL)
        return;
    rbt_free_nodes(tree, node->left);
    rbt_free_nodes(tree, node->right);
    free(node);
}

// Função para liberar a árvore inteira, incluindo o NIL e a estrutura da árvore
void rbt_free_tree(RedBlackTree *tree)
{
    if (!tree)
        return;
    rbt_free_nodes(tree, tree->root);
    free(tree->NIL);
    free(tree);
}

RedBlackTree *create_rbt_tree(int nil_value)
{
    RedBlackTree *tree = (RedBlackTree *)malloc(sizeof(RedBlackTree));
    tree->NIL = create_rbt_node(nil_value);
    tree->total_rotations = 0;
    tree->NIL->color = BLACK;
    tree->root = tree->NIL;
    tree->rbt_transplant = rbt_transplant;
    tree->rbt_search = rbt_search;
    tree->rbt_minimum = rbt_minimum;
    tree->rbt_delete_fixup = rbt_delete_fixup;
    tree->rbt_delete = rbt_delete;
    tree->rbt_insert_fixup = rbt_insert_fixup;
    tree->rbt_insert = rbt_insert;
    tree->rbt_right_rotate = rbt_right_rotate;
    tree->rbt_left_rotate = rbt_left_rotate;
    tree->rbt_print_tree = rbt_print_tree;
    tree->rbt_free_tree = rbt_free_tree;

    return tree;
}