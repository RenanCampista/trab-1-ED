#ifndef _NODE_H_
#define _NODE_H_

typedef void * data_type;
typedef struct Node Node;

struct Node {
    data_type data;
    Node *next;
};

Node *node_construct(data_type value, Node *next);
void node_destroy(Node *n, void (*destroy_fn)(data_type));

#endif