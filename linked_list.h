#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include "node.h"

typedef struct LinkedList LinkedList;

struct LinkedList {
    Node *head;
    int size;
};

LinkedList *linked_list_construct();
void linked_list_destroy(LinkedList *l, void (*destroy_fn)(data_type));
int linked_list_size(LinkedList *l);
void linked_list_push_front(LinkedList *l, data_type data);
void linked_list_print(LinkedList *l, void (*print_fn)(data_type));
data_type linked_list_get(LinkedList *l, int i);
data_type linked_list_pop_front(LinkedList *l, void (*destroy_fn)(data_type));
LinkedList *linked_list_reverse(LinkedList *l);
void linked_list_unique(LinkedList *l, int (*cmp_fn)(data_type, data_type), void (*destroy_fn)(data_type));
int linked_list_search(LinkedList *l, data_type data, int (*cmp_fn)(data_type, data_type));

#endif