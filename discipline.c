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

int discipline_compare_name(data_type data1, data_type data2) {
    Discipline *d1 = (Discipline *)data1;
    Discipline *d2 = (Discipline *)data2;
    return strcmp(d1->name, d2->name);
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
    linked_list_unique(students, student_compare_registration, NULL);
    linked_list_print(students, student_print_name);
    linked_list_destroy_node(students);
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

    // Adiciona os pré-requisitos diretos
    for (int i = 0; i < linked_list_size(d->prerequisites); i++) {
        Discipline *p = linked_list_get(d->prerequisites, i);
        linked_list_push_front(prerequisites, p);
        // Adiciona os pré-requisitos indiretos atraves de recusao
        LinkedList *aux = discipline_get_full_prerequisites(p);
        linked_list_concat(prerequisites, aux);
        linked_list_destroy(aux, NULL);
    }

    // Remove disciplinas repetidas
    linked_list_unique(prerequisites, discipline_compare_code, NULL);

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

int discipline_get_disapprovals(Discipline *d) {
    //Relatorio 5 (Reprovacoes por professor)
    /**
     * Para esse relatorio, fazer uma busca na lista de matriculas com o nome do professor e contabilizar o numero de reprovacoes
     * Bem provavel que eu tenha que criar uma lista para armazenar o nome do professor de o numero de matriculas
     * Nao sei ainda como salvar o professor e o numero de reprovacoes por ele
    */

   /*
    Ordenar duas listas juntas, passar uma função de comparar a quantidade de reprovação.
    Criar uma lista para armazenar o nome do professor
    Criar uma lista para salvar o numero de reprovações
   
   */
    int disapprovals = 0;

    for (int i = 0; i < linked_list_size(d->registrations); i++) {
        Registration *r = linked_list_get(d->registrations, i);
        if (registration_get_status(r) == DISAPPROVED)
            disapprovals++;
    }

    return disapprovals;
}

char *discipline_get_teacher(Discipline *d) {
    return d->teacher;
}

int discipline_is_approved(Discipline *d, Student *s) {
    //Relatorio 6
    //Buscar o aluno na lista de matriculas. Retornar 1 se aprovado e 0 se reprovado

    int idx = linked_list_search(d->registrations, s, registration_verify_student);
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
                if (!discipline_is_approved(p, s)) {
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

//Fazer uma função para comparar 2 disciplinas o percentual de aprovaçao
int discipline_compare_approval_percentage(data_type data1, data_type data2) {
    Discipline *d1 = (Discipline *)data1;
    Discipline *d2 = (Discipline *)data2;
    float percentage1 = discipline_get_approval_percentage(d1);
    float percentage2 = discipline_get_approval_percentage(d2);
    return percentage1 > percentage2;
}

void discipline_print_statistics(Discipline *d) {
    //Relatório 11
    printf("Codigo da disciplina: ");
    discipline_print_code(d);
    printf("\nNome da disciplina: ");
    discipline_print_name(d);
    //Num aprovacoes
    printf("Numero de aprovacoes: %d\n", discipline_get_number_approved(d));
    //Media das notas
    printf("Media das notas: %.2f\n\n", discipline_get_average_grade(d));
}