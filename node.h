#ifndef _NODE_H_
#define _NODE_H_

typedef struct Node Node;

struct Node {
    void *data;
    Node *next;
};



#endif