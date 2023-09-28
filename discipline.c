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

int discipline_verify_code(data_type data, data_type target_code) {
    Discipline *d = (Discipline *)data;
    char *code = (char *)target_code;
    return strcmp(d->code, code) == 0;
}

int discipline_compare_code(data_type data1, data_type data2) {
    Discipline *d1 = (Discipline *)data1;
    Discipline *d2 = (Discipline *)data2;
    return strcmp(d1->code, d2->code) == 0;
}

void discipline_add_prerequisite(Discipline *d, Discipline *p) {
    linked_list_push_front(d->prerequisites, p);
}

void discipline_print_name(data_type data) {
    Discipline *d = (Discipline *)data;
    printf("%s\n", d->name);
}

void discipline_show_students(Discipline *d) {
    //Relatorio 1
    LinkedList *students = linked_list_construct();

    for (int i = 0; i < linked_list_size(d->registrations); i++) {
        Registration *r = linked_list_get(d->registrations, i);
        Student *s = registration_get_student(r);
        linked_list_push_front(students, s);
    }

    //Eliminar alunos repetidos
    linked_list_unique(students, student_compare_registration, student_destroy);
    linked_list_print(students, student_print_name);
    linked_list_destroy(students, student_destroy);
}

LinkedList *discipline_get_direct_prerequisites(Discipline *d) {
    //Relatorio 2
    LinkedList *prerequisites = linked_list_construct();

    for (int i = 0; i < linked_list_size(d->prerequisites); i++) {
        Discipline *p = linked_list_get(d->prerequisites, i);
        linked_list_push_front(prerequisites, p);
    }

    //Inverter a lista
    prerequisites = linked_list_reverse(prerequisites);
    return prerequisites;
}

LinkedList *discipline_show_full_prerequisites(Discipline *d) {
    //Relatorio 3
    LinkedList *prerequisites = linked_list_construct();

    for (int i = 0; i < linked_list_size(d->prerequisites); i++) {
        Discipline *p = linked_list_get(d->prerequisites, i);
        linked_list_push_front(prerequisites, p);
        //Pegar os pre requisitos dessa disciplina
        LinkedList *aux = discipline_get_direct_prerequisites(p);

        //Adicionar os pre requisitos dessa disciplina na lista de pre requisitos
        for (int j = 0; j < linked_list_size(aux); j++) {
            Discipline *p2 = linked_list_get(aux, j);
            linked_list_push_front(prerequisites, p2);
        }
    }

    //Eliminar disciplinas repetidas
    linked_list_unique(prerequisites, discipline_compare_code, discipline_destroy);
    return prerequisites;
}

int discipline_has_registration(Discipline *d, Registration *r) {
    //Para o relatorio 4
    for (int i = 0; i < linked_list_size(d->registrations); i++) {
        Registration *r2 = linked_list_get(d->registrations, i);
        if (registration_compare_student(r2, r))
            return 1;
    }
    return 0;

    //Se retorna 1, pega a disciplina e adiciona na lista de disciplinas
    //Lembrar de retirar possiveis repeticoes e exibir no final.
}