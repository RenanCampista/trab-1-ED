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
void discipline_destroy(data_type data);
void discipline_read(Discipline *d);
void discipline_register_student(Discipline *d, Student *s);
int discipline_verify_code(data_type data, data_type target_code);
int discipline_compare_code(data_type data1, data_type data2);
void discipline_add_prerequisite(Discipline *d, Discipline *p);
void discipline_print_name(data_type data);
void discipline_print_data(data_type data);
int discipline_get_number_registrations(Discipline *d);
int discipline_get_number_approved(Discipline *d);
void discipline_print_statistics(Discipline *d);
#endif