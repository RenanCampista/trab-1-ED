#ifndef _STUDENT_H
#define _STUDENT_H

typedef struct Student Student;

struct Student {
    char name[100];
    char email[100];
    int registration_number;
};

#endif