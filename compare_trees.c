#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "rbt.h"

// Funcao auxiliar para calcular altura da AVL
int avl_height(AVLNode *node)
{
    if (!node)
        return 0;
    int left_height = avl_height(node->left);
    int right_height = avl_height(node->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

// Funcao auxiliar para calcular altura da RBT
int rbt_height(RedBlackTree *tree, RBTNode *node)
{
    if (node == tree->NIL || !node)
        return 0;
    int left_height = rbt_height(tree, node->left);
    int right_height = rbt_height(tree, node->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

// Funcao auxiliar para contar nos na AVL
int avl_count_nodes(AVLNode *node)
{
    if (!node)
        return 0;
    return 1 + avl_count_nodes(node->left) + avl_count_nodes(node->right);
}

// Funcao auxiliar para contar nos na RBT
int rbt_count_nodes(RedBlackTree *tree, RBTNode *node)
{
    if (node == tree->NIL || !node)
        return 0;
    return 1 + rbt_count_nodes(tree, node->left) + rbt_count_nodes(tree, node->right);
}

// Funcao auxiliar para armazenar chaves em vetor usando percurso em ordem AVL
void avl_inorder(AVLNode *node, int *arr, int *idx)
{
    if (!node)
        return;
    avl_inorder(node->left, arr, idx);
    arr[(*idx)++] = node->key;
    avl_inorder(node->right, arr, idx);
}

// Funcao auxiliar para armazenar chaves em vetor usando percurso em ordem RBT
void rbt_inorder(RedBlackTree *tree, RBTNode *node, int *arr, int *idx)
{
    if (node == tree->NIL || !node)
        return;
    rbt_inorder(tree, node->left, arr, idx);
    arr[(*idx)++] = node->key;
    rbt_inorder(tree, node->right, arr, idx);
}

// Funcao para comparar dois arrays de inteiros
int arrays_equal(int *a, int *b, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

void compare_trees(AVLTree *avl, RedBlackTree *rbt)
{
    printf("\n ============ Comparando AVL e Red-Black Tree: ============\n");

    // Alturas
    int avl_h = avl_height(avl->root);
    int rbt_h = rbt_height(rbt, rbt->root);
    printf("Altura AVL: %d\n", avl_h);
    printf("Altura RBT: %d\n", rbt_h);
    if (avl_h == rbt_h)
    {
        printf("-> Ambas tem a mesma altura\n\n");
    }
    else
    {
        printf("-> Diferem na altura\n\n");
    }

    // Tamanho (numero de nos)
    int avl_size = avl_count_nodes(avl->root);
    int rbt_size = rbt_count_nodes(rbt, rbt->root);
    printf("Numero de nos AVL: %d\n", avl_size);
    printf("Numero de nos RBT: %d\n", rbt_size);
    if (avl_size == rbt_size)
    {
        printf("-> Ambas tem o mesmo numero de nos\n\n");
    }
    else
    {
        printf("-> Diferem no numero de nos\n\n");
    }

    // Comparacao das raizes
    if (avl->root && rbt->root)
    {
        printf("Chave raiz AVL: %d\n", avl->root->key);
        printf("Chave raiz RBT: %d\n", rbt->root->key);
        if (avl->root->key == rbt->root->key)
        {
            printf("-> Raizes tem a mesma chave\n\n");
        }
        else
        {
            printf("-> Raizes tem chaves diferentes\n\n");
        }
    }
    else
    {
        printf("Uma ou ambas as arvores estao vazias\n\n");
    }

    // Comparacao das chaves (percurso em ordem)
    if (avl_size == rbt_size)
    {
        int *avl_keys = malloc(sizeof(int) * avl_size);
        int *rbt_keys = malloc(sizeof(int) * rbt_size);
        int idx_avl = 0, idx_rbt = 0;

        avl_inorder(avl->root, avl_keys, &idx_avl);
        rbt_inorder(rbt, rbt->root, rbt_keys, &idx_rbt);

        if (arrays_equal(avl_keys, rbt_keys, avl_size))
        {
            printf("-> Ambas as arvores possuem as mesmas chaves\n\n");
        }
        else
        {
            printf("-> As arvores possuem chaves diferentes\n\n");
        }

        free(avl_keys);
        free(rbt_keys);
    }
    else
    {
        printf("-> Tamanho diferente, nao e possivel comparar chaves diretamente\n\n");
    }
}
