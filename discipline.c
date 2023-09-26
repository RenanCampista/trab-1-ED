#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "discipline.h"

Discipline *discipline_constroy() {
    Discipline *d = (Discipline *) calloc(1, sizeof(Discipline));
    if (d == NULL)
        exit(printf("Problema ao alocar uma disciplina."));
    
    return d;
}

void discipline_destruct(Discipline *d) {
    if (d != NULL)
        free(d);
}