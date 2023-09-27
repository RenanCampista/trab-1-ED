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

void student_destroy(Student *s) {
    if (s != NULL)
        free(s);
}

void student_read(Student *s) {
    scanf("\n%[^;];%d;%[^\n]", s->name, &s->registration_number, s->email);
}

int student_compare_registration(data_type data, data_type target_code) {
    Student *student = (Student *)data;
    int *registration_number = (int *)target_code;
    return student->registration_number == *registration_number;
}