#include <stdio.h>
#include <stdlib.h>
#include "node.h"

Node *node_construct(data_type value, Node *next) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    if (n == NULL) 
        exit(printf("Problema ao alocar um no"));

    n->data = value;
    n->next = next;

    return n;
}

void node_destroy(Node *n) {
    free(n);
}