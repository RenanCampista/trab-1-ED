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

void student_read(Student *s) {
    scanf("\n%[^;];%d;%[^\n]", s->name, &s->registration_number, s->email);
}

int student_compare_registration(data_type data, data_type target_code) {
    Student *s = (Student *)data;
    int *registration_number = (int *)target_code;
    return s->registration_number == *registration_number;
}

void student_print_name(data_type data) {
    Student *s = (Student *)data;
    printf("%s\n", s->name);
}