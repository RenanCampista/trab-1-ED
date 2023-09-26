#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student *student_constroy() {
    Student *s = (Student *) calloc(1, sizeof(Student));
    if (s == NULL)
        exit(printf("Problema ao alocar um estudante."));
    
    return s;
}

void student_destruct(Student *s) {
    if (s != NULL)
        free(s);
}