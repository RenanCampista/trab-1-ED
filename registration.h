#ifndef _REGISTRATION_H
#define _REGISTRATION_H
#include "student.h"

typedef enum  {
    YES = 1,
    NO = 0
} Approved;

typedef struct Registration Registration;

struct Registration {
    Student *student;
    float final_grade;
    float presence_percentage;
    Approved approval_status;
};

#endif