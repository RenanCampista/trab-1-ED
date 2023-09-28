#ifndef _REGISTRATION_H
#define _REGISTRATION_H
#include "student.h"
#include "discipline.h"

typedef enum  {
    APPROVED = 1,
    DISAPPROVED = 0
} Approved;

typedef struct Registration Registration;

struct Registration {
    Student *student;
    float final_grade;
    float presence_percentage;
    Approved approval_status;
};

Registration *registration_construct();
void registration_destroy(data_type data);
void registration_read(Registration *r, Student *s);
Student *registration_get_student(data_type data);
int registration_compare_student(Registration *r1, Registration *r2);

#endif