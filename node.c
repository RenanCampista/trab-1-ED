#include <stdio.h>
#include <stdlib.h>
#include "node.h"

Node *node_construct(data_type value, Node *next) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    if (n == NULL) 
        exit(printf("Problema ao alocar um no.\n"));

    n->data = value;
    n->next = next;
    return n;
}

void node_destroy(Node *n, void (*destroy_fn)(data_type)) {
    if (n != NULL) {
        if (destroy_fn != NULL)
            destroy_fn(n->data);
        free(n);
    }
}