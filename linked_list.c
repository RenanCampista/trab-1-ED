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

void linked_list_sort_pair(LinkedList *princp, LinkedList *sec,int (*cmp_fn)(data_type, data_type)) {
    //princp é a lista que vai ser ordenada (reprovacoes)
    //sec é a lista que vai ser ordenada baseada na outra (nome professores)
    
    Node *n_pric = princp->head;
    Node *aux_princ;
    data_type data_aux_princ;

    Node *n_sec = sec->head;
    Node *aux_sec;
    data_type data_aux_sec;

    while(n_pric != NULL && n_sec != NULL) {
        aux_princ = n_pric->next;
        aux_sec = n_sec->next;

        while(aux_princ != NULL && aux_sec != NULL) {
            if (cmp_fn(n_pric->data, aux_princ->data)) {
                data_aux_princ = n_pric->data;
                n_pric->data = aux_princ->data;
                aux_princ->data = data_aux_princ;

                data_aux_sec = n_sec->data;
                n_sec->data = aux_sec->data;
                aux_sec->data = data_aux_sec;
            }
            aux_princ = aux_princ->next;
            
            aux_sec = aux_sec->next;
        }
        n_pric = n_pric->next;

        n_sec = n_sec->next;
    }
}

/*

void linked_list_print(LinkedList *l, void (*print_fn)(data_type)) {
    Node *n = l->head;

    while(n != NULL) {
        print_fn(n->data);
        n = n->next;
    }
}
*/

void linked_list_print_pair(LinkedList *l1, LinkedList *l2, void (*print_fn_1)(data_type),  void (*print_fn_2)(data_type)) {
    Node *n1 = l1->head;
    Node *n2 = l2->head;

    while(n1 != NULL) {
        print_fn_1(n1->data);
        n1 = n1->next;

        print_fn_2(n2->data);
        n2 = n2->next;
    }
}