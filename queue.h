#ifndef QUEUE_H
#define QUEUE_H

typedef struct node {
    int *client_socket;
    struct node *next;
} node;

void enqueue(int *client_socket);
int *dequeue();

#endif