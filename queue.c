#include <stdlib.h>
#include "queue.h"

node *head = NULL;
node *tail = NULL;

void enqueue(int *client_socket) {
    node *new = malloc(sizeof(node));
    new->client_socket = client_socket;
    new->next = NULL;

    if (tail == NULL) {
        head = new;
    }
    else {
        tail->next = new;
    }
    tail = new;
}

int *dequeue() {
    if (head == NULL) {
        return NULL;
    }
    else {
        int *client_socket = head->client_socket;
        node *temp = head;
        head = head->next;
        if (head == NULL) {
            tail = NULL;
        }
        free(temp);
        return client_socket;
    }
}