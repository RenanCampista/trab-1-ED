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
void student_destroy(Student *s);
void student_read(Student *s);
int student_compare_registration(data_type data, data_type target_code);
void student_print_name(data_type data);

#endif