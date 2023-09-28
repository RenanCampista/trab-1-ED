#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registration.h"

Registration *registration_construct() {
    Registration *r = (Registration *) calloc(1, sizeof(Registration));
    if (r == NULL)
        exit(printf("Problema ao alocar uma matrícula."));
    
    return r;
}

void registration_destroy(data_type data) {
    Registration *r = (Registration *)data;
    free(r);
}

void registration_read(Registration *r, Student *s) {
    int status;
    scanf("%f;%f;%d",&r->final_grade, &r->presence_percentage, &status);
    r->approval_status = status == 1 ? APPROVED : DISAPPROVED ;
    r->student = s;
}

Student *registration_get_student(data_type data) {
    Registration *r = (Registration *)data;
    return r->student;
}

int registration_compare_student(Registration *r1, Registration *r2) {
    return student_compare_registration(r1->student, r2->student);
}