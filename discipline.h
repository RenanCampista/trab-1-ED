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
void discipline_read(Discipline *d, FILE *f);
void discipline_register_student(Discipline *d, Student *s, FILE *f);
int discipline_verify_code(data_type data, data_type target_code);
int discipline_compare_code(data_type data1, data_type data2);
int discipline_compare_name(data_type data1, data_type data2);
int discipline_compare_approval_percentage(data_type data1, data_type data2);
void discipline_add_prerequisite(Discipline *d, Discipline *p);
void discipline_print_name(data_type data);
void discipline_print_teacher(data_type data);
void discipline_print_code(data_type data);
void discipline_print_data(data_type data);
void discipline_print_name_and_teacher(data_type data);
void discipline_print_statistics(Discipline *d);
void discipline_show_students(Discipline *d);
int discipline_has_registration(Discipline *d, Student *s);
int discipline_is_approved(Discipline *d, Student *s);
void discipline_check_inconsistency(Discipline *d);
int discipline_check_prerequisites(Discipline *d);
int discipline_check_prerequisites_disapproved(Discipline *d);
LinkedList *discipline_get_direct_prerequisites(Discipline *d);
LinkedList *discipline_get_full_prerequisites(Discipline *d);
char *discipline_get_teacher(Discipline *d);
int discipline_get_number_registrations(Discipline *d);
int discipline_get_number_approved(Discipline *d);
float discipline_get_average_grade(Discipline *d);
float discipline_get_approval_percentage(Discipline *d);
int discipline_get_disapprovals(Discipline *d);
LinkedList *discipline_get_registrations(Discipline *d);

#endif