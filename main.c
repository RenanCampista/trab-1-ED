#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "discipline.h"
#include "registration.h"
#include "student.h"


int main() {
    int number_students = 0, number_disciplines = 0, number_registrations = 0, number_prerequisites = 0;
    LinkedList *students = linked_list_construct();
    LinkedList *disciplines = linked_list_construct();

    scanf("\n%d", &number_students);
    /**
     * Lê os dados dos alunos e os insere na lista de alunos
    */
    for (int i = 0; i < number_students; i++) {
        Student *s = student_construct();
        student_read(s);
        linked_list_push_front(students, s);
    }

    scanf("\n%d", &number_disciplines);
    /**
     * Lê os dados das disciplinas e os insere na lista de disciplinas
    */
    for (int i = 0; i < number_disciplines; i++) {
        Discipline *d = discipline_construct();
        discipline_read(d);
        linked_list_push_front(disciplines, d);
    }

    scanf("\n%d", &number_prerequisites);
    /**
     * Busca a disciplina pelo código e a pré-requisito pelo código
     * Em seguida, adiciona a pré-requisito na lista de pré-requisitos da disciplina
    */
    for (int i = 0; i < number_prerequisites; i++) {
        data_type discipline_code[50], prerequisite_code[50];

        scanf("\n%50[^;];%s", (char*)discipline_code, (char*)prerequisite_code);

        int disc_idx = linked_list_search(disciplines, discipline_code, discipline_verify_code);
        int pre_idx = linked_list_search(disciplines, prerequisite_code, discipline_verify_code);

        if (disc_idx == -1 || pre_idx == -1) 
            continue;
        
        Discipline *d = linked_list_get(disciplines, disc_idx);
        Discipline *p = linked_list_get(disciplines, pre_idx);
        discipline_add_prerequisite(d, p);
    }


    scanf("\n%d", &number_registrations);
    /**
     * Busca a disciplina pelo código e o aluno pelo número de matrícula
     * Em seguida, registra o aluno em uma das disciplinas da lista
    */
    for (int i = 0; i < number_registrations; i++) {
        data_type discipline_code[50];
        int registration_number;

        scanf("\n%50[^;];%d;", (char*)discipline_code, &registration_number);

        int disc_idx = linked_list_search(disciplines, discipline_code, discipline_verify_code);
        int stu_idx = linked_list_search(students, &registration_number, student_verify_registration);
        //printf("disc_idx: %d e stu_idx: %d\n", disc_idx, stu_idx);
        if (disc_idx == -1 || stu_idx == -1) {
            //limpar a linha
            char line[100];
            scanf("%[^\n]", line);
            continue;
        }
        Discipline *d = linked_list_get(disciplines, disc_idx);
        Student *s = linked_list_get(students, stu_idx);
        discipline_register_student(d, s);
    }

    //Relatorio 1
    char code_dsc[50];
    scanf("\n%[^\n]", code_dsc);
    int idx = linked_list_search(disciplines, code_dsc, discipline_verify_code);
    Discipline *d = linked_list_get(disciplines, idx);
    discipline_show_students(d);

    //Relatorio 2 funcionando
    // char code_dsc[50];
    // scanf("\n%[^\n]", code_dsc);
    // int idx = linked_list_search(disciplines, code_dsc, discipline_verify_code);
    // Discipline *d = linked_list_get(disciplines, idx);
    // LinkedList *prerequisites = discipline_get_direct_prerequisites(d);
    // linked_list_print(prerequisites, discipline_print_name);
    // linked_list_destroy_node(prerequisites);


    
    //Relatorio 4 funcionando
    // int registration_std = 0;
    // scanf("\n%d", &registration_std);
    // int idx_r = linked_list_search(students, &registration_std, student_verify_registration);
    // Student *s = linked_list_get(students, idx_r);
    // LinkedList *registrations_student = linked_list_construct();
    // for (int i = 0; i < linked_list_size(disciplines); i++) {
    //     Discipline *d = linked_list_get(disciplines, i);

    //     if (discipline_has_registration(d, s)) {
    //         linked_list_push_front(registrations_student, d);
    //     }
    // }
    // //remover disciplinas repetidas
    // linked_list_unique(registrations_student, discipline_compare_code, discipline_destroy);
    // linked_list_print(registrations_student, discipline_print_name);
    // linked_list_destroy_node(registrations_student);




   // linked_list_print(disciplines, discipline_print_data);

    /**
     * Relatorio 10
     * Obter o numero de disciplinas que o aluno cursou
    */
    // for (int i = 0; i < number_students; i++) {
    //     Student *s = linked_list_get(students, i);
    //     student_print_name(s);
    //     student_print_registration_number(s);


    //     int count_approved = 0, count_registered = 0;
    //     float average_grade = 0;
    //     //Verificar a quantidade de disciplinas que o aluno foi aprovado
    //     for (int j = 0; j < number_disciplines; j++) {
    //         Discipline *d = linked_list_get(disciplines, j);

    //         for (int k = 0; k < discipline_get_number_registrations(d); k++) {
    //             Registration *r = linked_list_get(d->registrations, k);
    //             if (registration_verify_student(r, s)) {
    //                 if (registration_get_status(r) == APPROVED) {
    //                     count_approved++;
    //                 }
    //                 average_grade += registration_get_grade(r);
    //                 count_registered++;
    //                 break;
    //             }
    //         }
    //     }
    //     average_grade /= count_registered;
    //     printf(";%d;%.2f\n", count_approved, average_grade);
        
    // }

    // /**
    //  * Relatorio 11
    //  * Informações sobre cada disciplina
    //  * Ordenar as disciplinas pelo percentual de aprovacao
    // */
    // for (int i = 0; i < number_disciplines; i++) {
    //     Discipline *d = linked_list_get(disciplines, i);
    //     discipline_print_statistics(d);
    // }

    // /**
    //  * Relatorio 12
    //  * Ler o codigo de uma disciplina e remover todas as menções à disciplina nas estruturas de dados
    // */
    // char discipline_code[50];
    // scanf("\n%[^\n]", discipline_code);
    // int disc_idx = linked_list_search(disciplines, &discipline_code, discipline_compare_code);
    // if (disc_idx != -1) {
    //     Discipline *d = linked_list_get(disciplines, disc_idx);

    //     //Remover de todos os prerequisitos
    //     for (int i = 0; i < number_disciplines; i++) {
    //         Discipline *p = linked_list_get(disciplines, i);
    //         linked_list_remove(p->prerequisites, d, discipline_destroy);
    //     }
    //     linked_list_remove(disciplines, d, discipline_destroy);
    // }

    /**
     * Desaloca os alunos e as disciplinas
    */
    linked_list_destroy(students, student_destroy);
    linked_list_destroy(disciplines, discipline_destroy);
    return 0;
}