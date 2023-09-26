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

Discipline *discipline_construct();
void discipline_destroy(Discipline *d);
void discipline_read(Discipline *d);
void discipline_register_student(Discipline *d, Student *s);
int discipline_compare_code(Discipline *d, char *code);
#endif