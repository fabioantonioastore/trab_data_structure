#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode
{
    struct QueueNode *next;
    struct QueueNode *prev;
    void *data;
} QueueNode;

typedef struct Queue
{
    QueueNode *head; // início da fila (remoção)
    QueueNode *tail; // fim da fila (inserção)
    void (*enqueue)(struct Queue *, void *);
    void *(*dequeue)(struct Queue *);
    int (*is_empty)(struct Queue *);
} Queue;

Queue *create_queue();

#endif