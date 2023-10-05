#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

LinkedList *linked_list_construct() {
    LinkedList *l = (LinkedList *) calloc(1, sizeof(LinkedList));
    if (l == NULL)
        exit(printf("Problema ao alocar uma lista encadeada.\n"));

    return l;
}

void linked_list_destroy(LinkedList *l, void (*destroy_fn)(data_type)) {
    Node *n = l->head;
    Node *aux;

    while(n != NULL) {
        aux = n->next;
        node_destroy(n, destroy_fn);
        n = aux;
    }
    free(l);
}

void linked_list_destroy_node(LinkedList *l) {
    Node *n = l->head;
    Node *aux;

    while(n != NULL) {
        aux = n->next;
        free(n);
        n = aux;
    }

    free(l);
}

int linked_list_size(LinkedList *l) {
    return l->size;
}

void linked_list_push_front(LinkedList *l, data_type data) {
    Node *n = node_construct(data, l->head);
    l->head = n;
    l->size++;
}

void linked_list_remove(LinkedList *l, data_type value, void (*destroy_fn)(data_type)) {
    Node *n = l->head;
    Node *aux;

    if (n == NULL)
        return;

    if (n->data == value) {
        l->head = n->next;
        node_destroy(n, destroy_fn);
        l->size--;
        return;
    }

    while(n->next != NULL) {
        if (n->next->data == value) {
            aux = n->next;
            n->next = aux->next;
            node_destroy(aux, destroy_fn);
            l->size--;
            return;
        }
        n = n->next;
    }
}

void linked_list_print(LinkedList *l, void (*print_fn)(data_type)) {
    Node *n = l->head;

    while(n != NULL) {
        print_fn(n->data);
        n = n->next;
    }
}

data_type linked_list_get(LinkedList *l, int i) {
    int count = 0;
    Node *n = l->head;

    while(count < i && n != NULL) {
        n = n->next;
        count++;
    }
    return n->data;
}

data_type linked_list_pop_front(LinkedList *l, void (*destroy_fn)(data_type)) {
    Node *n = l->head;
    data_type data_removed = n->data;
    l->head = n->next;
    node_destroy(n, destroy_fn);
    l->size--;
    return data_removed;
}

LinkedList *linked_list_reverse(LinkedList *l) {
    LinkedList *r = linked_list_construct();
    Node *n = l->head;

    while(n != NULL) {
        linked_list_push_front(r, n->data);
        n = n->next;
    }
    linked_list_destroy_node(l);
    return r;
}

void linked_list_unique(LinkedList *l, int (*cmp_fn)(data_type, data_type), void (*destroy_fn)(data_type)) {
    Node *n = l->head;
    Node *aux;
    while(n != NULL) {
        aux = n->next;
        while(aux != NULL) {
            if (cmp_fn(n->data, aux->data)) {
                n->next = aux->next;
                if (destroy_fn != NULL)
                    node_destroy(aux, destroy_fn);
                else
                    free(aux);
                aux = n;
                l->size--;
            }
            aux = aux->next;
        }
        n = n->next;
    }
}

int linked_list_search(LinkedList *l, data_type data, int (*cmp_fn)(data_type, data_type)) {
    Node *n = l->head;
    int count = 0;

    while(n != NULL) {
        if (cmp_fn(n->data, data))
            return count;
        n = n->next;
        count++;
    }
    return -1;
}

void linked_list_sort(LinkedList *l, int (*cmp_fn)(data_type, data_type)) {
    Node *n = l->head;
    Node *aux;
    data_type data_aux;

    while(n != NULL) {
        aux = n->next;
        while(aux != NULL) {
            if (cmp_fn(n->data, aux->data)) {
                data_aux = n->data;
                n->data = aux->data;
                aux->data = data_aux;
            }
            aux = aux->next;
        }
        n = n->next;
    }
}

// void linked_list_unique(LinkedList *l, int (*cmp_fn)(data_type, data_type), void (*destroy_fn)(data_type)) {
//     Node *n = l->head;
//     Node *aux;

//     while(n != NULL) {
//         aux = n->next;
//         while(aux != NULL) {
//             if (cmp_fn(n->data, aux->data)) {
//                 if (destroy_fn != NULL)
//                     destroy_fn(aux->data);
//                 else
//                     free(aux->data);
//             }
//             aux = aux->next;
//         }
//         n = n->next;
//     }
// }