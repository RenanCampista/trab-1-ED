#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "discipline.h"

Discipline *discipline_construct() {
    Discipline *d = (Discipline *) calloc(1, sizeof(Discipline));
    if (d == NULL)
        exit(printf("Problema ao alocar uma disciplina."));
    
    return d;
}

void discipline_destroy(Discipline *d) {
    if (d != NULL)
        free(d);
}

void discipline_read(Discipline *d) {
    scanf("\n%[^;];%[^;];%[^\n]", d->name, d->code, d->teacher);
}