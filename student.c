#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student *student_construct() {
    Student *s = (Student *) calloc(1, sizeof(Student));
    if (s == NULL)
        exit(printf("Problema ao alocar um estudante."));
    
    return s;
}

void student_destroy(data_type data) {
    Student *s = (Student *)data;
    free(s);
}

void student_read(Student *s, FILE *f) {
    fscanf(f, "\n%[^;];%d;%[^\n]", s->name, &s->registration_number, s->email);
}

int student_verify_registration(data_type data, data_type target_code) {
    Student *s = (Student *)data;
    int *registration_number = (int *)target_code;
    return s->registration_number == *registration_number;
}

int student_get_registration_number(Student *s) {
    return s->registration_number;
}

void student_print_name(data_type data) {
    Student *s = (Student *)data;
    printf("%s\n", s->name);
}

void student_print_registration_number(Student *s) {
   // Student *s = (Student *)data;
    printf("%d", s->registration_number);
}

int student_compare_registration(data_type data1, data_type data2) {
    Student *s1 = (Student *)data1;
    Student *s2 = (Student *)data2;
    return s1->registration_number == s2->registration_number;
}
