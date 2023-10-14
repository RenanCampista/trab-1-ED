#ifndef _STUDENT_H
#define _STUDENT_H
#include "node.h"

typedef struct Student Student;

struct Student {
    char name[100];
    char email[100];
    int registration_number;
};

Student *student_construct();
void student_destroy(data_type data);
void student_read(Student *s, FILE *f);
int student_verify_registration(data_type data, data_type target_code);
int student_get_registration_number(Student *s);
void student_print_name(data_type data);
void student_print_registration_number(Student *s);
void student_print_all_data(data_type data);
int student_compare_registration(data_type data1, data_type data2);

#endif