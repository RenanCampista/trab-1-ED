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
    scanf("%f;%f;%d ", &r->final_grade, &r->presence_percentage, &status);
    r->approval_status = status == 1 ? APPROVED : DISAPPROVED ;
    r->student = s;
}

int registration_get_status(Registration *r) {
    return r->approval_status;
}

Student *registration_get_student(data_type data) {
    Registration *r = (Registration *)data;
    return r->student;
}

float registration_get_grade(data_type data) {
    Registration *r = (Registration *)data;
    return r->final_grade;
}

int registration_get_registration_number(data_type data) {
    Registration *r = (Registration *)data;
    return student_get_registration_number(r->student);
}

int registration_verify_student(data_type data, data_type target_student) {
    Registration *r = (Registration *)data;
    Student *s = (Student *)target_student;
    return student_compare_registration(r->student, s);
}

void registration_print(Registration *r) {
    student_print_registration_number(r->student);
    printf(";");
    printf("%.2f;%.2f;%d\n", r->final_grade, r->presence_percentage, r->approval_status);
}

int registration_compare_student(Registration *r1, Registration *r2) {
    return student_compare_registration(r1->student, r2->student);
}

int registration_check_inconsistency(Registration *r) {
   if (r->approval_status == APPROVED) {
        if (r->final_grade < 5.0 || r->presence_percentage < 75.0) 
            return 1;
        else 
            return 0;
        
   } else {
        if (r->final_grade >= 5.0 || r->presence_percentage >= 75.0) 
            return 1;
        else 
            return 0;
        
   }
}


