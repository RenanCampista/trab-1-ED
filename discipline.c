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
    if (d != NULL) {
        linked_list_destroy(d->registrations, registration_destroy);
    
        linked_list_destroy(d->prerequisites, NULL);
        free(d);
    }
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

void discipline_print_teacher(data_type data) {
    Discipline *d = (Discipline *)data;
    printf("%s\n", d->teacher);
}

void discipline_print_code(data_type data) {
    Discipline *d = (Discipline *)data;
    printf("%s", d->code);
}

void discipline_print_data(data_type data) {
    Discipline *d = (Discipline *)data;
    printf("Disciplina: %s\n", d->name);
    printf("Pre requisitos: ");
    for (int i = 0; i < linked_list_size(d->prerequisites); i++) {
        Discipline *p = linked_list_get(d->prerequisites, i);
        printf("%s ", p->name);
    }
    printf("\n\n");
    printf("Alunos matriculados: ");
    for (int i = 0; i < linked_list_size(d->registrations); i++) {
        Registration *r = linked_list_get(d->registrations, i);
        Student *s = registration_get_student(r);
        student_print_name(s);
        printf("\n");
    }
    printf("\n");

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

int discipline_get_number_registrations(Discipline *d) {
    return linked_list_size(d->registrations);
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

LinkedList *discipline_get_full_prerequisites(Discipline *d) {
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

int discipline_has_registration(Discipline *d, Student *s) {
    //Para o relatorio 4
    for (int i = 0; i < linked_list_size(d->registrations); i++) {
        Registration *r2 = linked_list_get(d->registrations, i);
        if (registration_verify_student(r2, s))
            return 1;
    }
    return 0;

    //Se retorna 1, pega a disciplina e adiciona na lista de disciplinas
    //Lembrar de retirar possiveis repeticoes e exibir no final.
}

int discipline_get_disapprovals_by_teacher(Discipline *d) {
    //Relatorio 5 (Reprovacoes por professor)
    /**
     * Para esse relatorio, fazer uma busca na lista de matriculas com o nome do professor e contabilizar o numero de reprovacoes
     * Bem provavel que eu tenha que criar uma lista para armazenar o nome do professor de o numero de matriculas
     * Nao sei ainda como salvar o professor e o numero de reprovacoes por ele
    */
    int disapprovals = 0;

    for (int i = 0; i < linked_list_size(d->registrations); i++) {
        Registration *r = linked_list_get(d->registrations, i);
        if (registration_get_status(r) == DISAPPROVED)
            disapprovals++;
    }

    return disapprovals;
}

int discipline_is_approved(Discipline *d, int registration_number) {
    //Relatorio 6
    //Buscar o aluno na lista de matriculas. Retornar 1 se aprovado e 0 se reprovado
    int idx = linked_list_search(d->registrations, &registration_number, student_compare_registration);
    if (idx == -1)
        return 0;

    Registration *r = linked_list_get(d->registrations, idx);
    return registration_get_status(r) == APPROVED;
    /**
     * Na main, se retornar 1, adicionar a uma lista para entao ordenar ela no final
    */
}

void discipline_check_inconsistency(Discipline *d) {
    //Relatorio 7 Verificar se na disciplina ha alguma inconsistencia na matricula
    //Discipline *d = (Discipline *)data;

    for (int i = 0; i < linked_list_size(d->registrations); i++) {
        Registration *r = linked_list_get(d->registrations, i);
        if (registration_check_inconsistency(r)) {
            discipline_print_code(d);
            printf(";");
            registration_print(r);
            // Student *s = registration_get_student(r);
            // printf("%s\n", student_get_name(s));
        }
    }
}

int discipline_check_prerequisites(Discipline *d) {
    //Relatorio 8
    //Verificar se os alunos da disciplina cursaram os pre requisitos e retornar o total de alunos que nao cursaram os pre requisitos se houver
    int total = 0, aux = 0;

    for (int i = 0; i < linked_list_size(d->registrations); i++) {
        Registration *r = linked_list_get(d->registrations, i);
        //Student *s = registration_get_student(r);
        LinkedList *prerequisites = discipline_get_full_prerequisites(d);

        aux = 0;
        for (int j = 0; j < linked_list_size(prerequisites); j++) {
            Discipline *p = linked_list_get(prerequisites, j);
            Student *s = registration_get_student(r);
            if (!discipline_has_registration(p, s)) {
                aux = 1;

            }
        }
        if (aux == 1)
            total++;
    }

    return total;
}

int discipline_check_prerequisites_disapproved(Discipline *d) {
    //Relatorio 9
    //Alunos que cursaram os pre requisitos mas foram reprovados
    int total = 0, aux = 0;

    for (int i = 0; i < linked_list_size(d->registrations); i++) {
        Registration *r = linked_list_get(d->registrations, i);
        //Student *s = registration_get_student(r);
        LinkedList *prerequisites = discipline_get_full_prerequisites(d);

        aux = 0;
        for (int j = 0; j < linked_list_size(prerequisites); j++) {
            Discipline *p = linked_list_get(prerequisites, j);
            Student *s = registration_get_student(r);
            if (discipline_has_registration(p, s)) {
                if (!discipline_is_approved(p, registration_get_registration_number(r))) {
                    aux = 1;
                }
            }
        }
        if (aux == 1)
            total++;
    }
    return total;
}

int discipline_get_number_approved(Discipline *d) {
    int approved = 0;

    for (int i = 0; i < linked_list_size(d->registrations); i++) {
        Registration *r = linked_list_get(d->registrations, i);
        if (registration_get_status(r) == APPROVED)
            approved++;
    }

    return approved;
}

float discipline_get_average_grade(Discipline *d) {
    float average = 0;

    for (int i = 0; i < linked_list_size(d->registrations); i++) {
        Registration *r = linked_list_get(d->registrations, i);
        average += registration_get_grade(r);
    }

    return average / linked_list_size(d->registrations);
}

float discipline_get_approval_percentage(Discipline *d) {
    int approved = discipline_get_number_approved(d);
    return (float)approved / linked_list_size(d->registrations);
}

void discipline_print_statistics(Discipline *d) {
    //Relatório 11
    discipline_print_code(d);
    printf(";");
    discipline_print_name(d);
    //Num aprovacoes
    printf("%d;", discipline_get_number_approved(d));
    //Media das notas
    printf("%.2f;", discipline_get_average_grade(d));
}