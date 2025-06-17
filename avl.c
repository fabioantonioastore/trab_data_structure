#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "utils.h"
#include "queue.h"


int get_height(AVLNode *node)
{
    if (node)
    {
        return node->height;
    }
    return 0;
}

int get_balance_factor(AVLNode *node)
{
    if (node)
    {
        return get_height(node->left) - get_height(node->right);
    }
    return 0;
}

AVLNode *get_min_node(AVLNode *node)
{
    if (!node || !node->left)
    {
        return node;
    }
    return get_min_node(node->left);
}

// O(log n)
AVLNode *avl_search(AVLTree *tree, int key)
{
    AVLNode *node = tree->root;
    while (node && key != node->key)
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

AVLNode *create_avl_node(int key)
{
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// O(1)
AVLNode *avl_right_rotate(AVLTree* tree, AVLNode *node)
{
    tree->total_rotations += 1;
    AVLNode *A = node->left;
    AVLNode *Y = A->right;

    A->right = node;
    node->left = Y;

    node->height = 1 + max(
                           get_height(node->left),
                           get_height(node->right));

    A->height = 1 + max(
                        get_height(A->left),
                        get_height(A->right));

    return A;
}

// O(1)
AVLNode *avl_left_rotate(AVLTree* tree, AVLNode *node)
{
    tree->total_rotations += 1;
    AVLNode *B = node->right;
    AVLNode *Y = B->left;

    B->left = node;
    node->right = Y;

    node->height = 1 + max(
                           get_height(node->left),
                           get_height(node->right));

    B->height = 1 + max(
                        get_height(B->left),
                        get_height(B->right));

    return B;
}

// O(log n)
AVLNode *avl_insert(AVLTree* tree, AVLNode *node, int key)
{
    if (!node)
    {
        return create_avl_node(key);
    }
    else if (key < node->key)
    {
        node->left = avl_insert(tree, node->left, key);
    }
    else
    {
        node->right = avl_insert(tree, node->right, key);
    }

    node->height = 1 + max(
                           get_height(node->left),
                           get_height(node->right));

    // Balance Tree

    int balance_factor = get_balance_factor(node);

    if (balance_factor > 1 && key < node->left->key)
    {
        return avl_right_rotate(tree, node);
    }
    if (balance_factor < -1 && key > node->right->key)
    {
        return avl_left_rotate(tree, node);
    }
    if (balance_factor > 1 && key > node->left->key)
    {
        node->left = avl_left_rotate(tree, node->left);
        return avl_right_rotate(tree, node);
    }
    if (balance_factor < -1 && key < node->right->key)
    {
        node->right = avl_right_rotate(tree, node->right);
        return avl_left_rotate(tree, node);
    }

    return node;
}

// O(log n)
AVLNode *avl_delete(AVLTree* tree, AVLNode *node, int key)
{
    if (!node)
    {
        return NULL;
    }
    else if (key < node->key)
    {
        node->left = avl_delete(tree, node->left, key);
    }
    else if (key > node->key)
    {
        node->right = avl_delete(tree, node->right, key);
    }
    else
    {
        if (!node->left)
        {
            AVLNode *temp_node = node->right;
            free(node);
            return temp_node;
        }
        else if (!node->right)
        {
            AVLNode *temp_node = node->left;
            free(node);
            return temp_node;
        }
        AVLNode *temp_node = get_min_node(node->right);
        node->key = temp_node->key;
        node->right = avl_delete(tree, node->right, temp_node->key);
    }
    node->height = 1 + max(
                           get_height(node->left),
                           get_height(node->right));

    // Balance Tree

    int balance_factor = get_balance_factor(node);

    if (balance_factor > 1 && get_balance_factor(node->left) >= 0)
    {
        return avl_right_rotate(tree, node);
    }
    if (balance_factor < -1 && get_balance_factor(node->right) <= 0)
    {
        return avl_left_rotate(tree, node);
    }
    if (balance_factor > 1 && get_balance_factor(node->left) < 0)
    {
        node->left = avl_left_rotate(tree, node->left);
        return avl_right_rotate(tree, node);
    }
    if (balance_factor < -1 && get_balance_factor(node->right) > 0)
    {
        node->right = avl_right_rotate(tree, node->right);
        return avl_left_rotate(tree, node);
    }

    return node;
}

void print_search(AVLTree *tree, int key)
{
    AVLNode *result_node = avl_search(tree, key);

    if (result_node)
    {
        printf("%d\n", result_node->key);
    }
    else
    {
        printf("Not found\n");
    }
}

void avl_print_tree(AVLTree *tree)
{
    AVLNode *root = tree->root;
    if (root)
    {
        Queue *queue = create_queue();
        queue->enqueue(queue, root);

        while (!queue->is_empty(queue))
        {
            AVLNode *node = queue->dequeue(queue);
            printf("Key: %d\t Height: %d\t Balance Factor: %d\n", node->key, node->height, get_balance_factor(node));

            if (node->left)
            {
                queue->enqueue(queue, node->left);
            }
            if (node->right)
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

// Função para liberar todos os nós da AVL recursivamente
void avl_free_nodes(AVLNode *node)
{
    if (!node)
        return;
    avl_free_nodes(node->left);
    avl_free_nodes(node->right);
    free(node);
}

// Função para liberar a árvore AVL
void avl_free_tree(AVLTree *tree)
{
    if (!tree)
        return;
    avl_free_nodes(tree->root);
    free(tree);
}

AVLTree *create_avl_tree()
{
    AVLTree *tree = (AVLTree *)malloc(sizeof(AVLTree));
    tree->root = NULL;
    tree->total_rotations = 0;
    tree->avl_delete = avl_delete;
    tree->avl_insert = avl_insert;
    tree->get_balance_factor = get_balance_factor;
    tree->get_height = get_height;
    tree->get_min_node = get_min_node;
    tree->avl_left_rotate = avl_left_rotate;
    tree->avl_right_rotate = avl_right_rotate;
    tree->print_search = print_search;
    tree->avl_print_tree = avl_print_tree;
    tree->avl_search = avl_search;
    tree->avl_free_tree = avl_free_tree; // adiciona ponteiro para a função free
    return tree;
}
