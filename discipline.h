#ifndef _DISCIPLINE_H_
#define _DISCIPLINE_H_
#include "linked_list.h"
#include "registration.h"

typedef struct Discipline Discipline;

struct Discipline {
    char name[100];
    char code[50];
    char teacher[100];
    LinkedList *registrations;
    LinkedList *prerequisites;
};
#endif