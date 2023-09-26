#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include "node.h"

typedef struct LikedList LinkedList;

struct LinkedList {
    Node *head;
    int size;
};

#endif