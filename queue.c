#include <stdlib.h>
#include "queue.h"

QueueNode *create_queue_node(void *data)
{
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void enqueue(Queue *queue, void *data)
{
    QueueNode *new_node = create_queue_node(data);
    if (!queue->head)
    {
        queue->head = new_node;
        return;
    }
    QueueNode *node = queue->head;
    while (node->next)
    {
        node = node->next;
    }
    node->next = new_node;
    new_node->prev = node;
}

void *dequeue(Queue *queue)
{
    if (!queue->head)
    {
        return NULL;
    }
    QueueNode *node = queue->head;
    void *data = node->data;
    queue->head = node->next;
    if (queue->head)
    {
        queue->head->prev = NULL;
    }
    free(node);
    return data;
}

int is_empty(Queue *queue)
{
    if (!queue->head)
    {
        return 1;
    }
    return 0;
}

Queue *create_queue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->dequeue = dequeue;
    queue->enqueue = enqueue;
    queue->is_empty = is_empty;
    return queue;
}