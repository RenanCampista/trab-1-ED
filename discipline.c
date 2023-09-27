#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "discipline.h"

Discipline *discipline_construct() {
    Discipline *d = (Discipline *) calloc(1, sizeof(Discipline));
    if (d == NULL)
        exit(printf("Problema ao alocar uma disciplina."));
    d->registrations = linked_list_construct();
    d->prerequisites = linked_list_construct();
    return d;
}

void discipline_destroy(data_type data) {
    Discipline *d = (Discipline *)data;
    linked_list_destroy(d->registrations, registration_destroy);
    linked_list_destroy(d->prerequisites, discipline_destroy);
    free(d);
}

void discipline_read(Discipline *d) {
    scanf("\n%[^;];%[^;];%[^\n]", d->name, d->code, d->teacher);
}

void discipline_register_student(Discipline *d, Student *s) {
    Registration *r = registration_construct();
    registration_read(r, s);
    linked_list_push_front(d->registrations, r);
}

int discipline_compare_code(data_type data, data_type target_code) {
    Discipline *d = (Discipline *)data;
    char *code = (char *)target_code;
    return strcmp(d->code, code) == 0;
}

void discipline_add_prerequisite(Discipline *d, Discipline *p) {
    linked_list_push_front(d->prerequisites, p);
}

void discipline_print_name(data_type data) {
    Discipline *d = (Discipline *)data;
    printf("%s\n", d->name);
}