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
    for (int i = 0; i < number_disciplines; i++) {
        char discipline_code[50], prerequisite_code[50];
        scanf("\n%[^;];%[^\n]", discipline_code, prerequisite_code);

        int disc_idx = linked_list_search(disciplines, &discipline_code, discipline_verify_code);
        int pre_idx = linked_list_search(disciplines, &prerequisite_code, discipline_verify_code);
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
        char discipline_code[50];
        int registration_number;
        scanf("\n%[^;];%d,", discipline_code, &registration_number);


        int disc_idx = linked_list_search(disciplines, &discipline_code, discipline_compare_code);
        int stu_idx = linked_list_search(students, &registration_number, student_compare_registration);
        if (disc_idx == -1 || stu_idx == -1)
            continue;

        Discipline *d = linked_list_get(disciplines, disc_idx);
        Student *s = linked_list_get(students, stu_idx);
        discipline_register_student(d, s);
    }
    


    /**
     * Relatorio 10
     * Obter o numero de disciplinas que o aluno cursou
    */
    for (int i = 0; i < number_students; i++) {
        Student *s = linked_list_get(students, i);
        student_print_name(s);
        student_print_registration_number(s);


        int count_approved = 0, count_registered = 0;
        float average_grade = 0;
        //Verificar a quantidade de disciplinas que o aluno foi aprovado
        for (int j = 0; j < number_disciplines; j++) {
            Discipline *d = linked_list_get(disciplines, j);

            for (int k = 0; k < discipline_get_number_registrations(d); k++) {
                Registration *r = linked_list_get(d->registrations, k);
                if (registration_verify_student(r, s)) {
                    if (registration_get_status(r) == APPROVED) {
                        count_approved++;
                    }
                    average_grade += registration_get_grade(r);
                    count_registered++;
                    break;
                }
            }
        }
        average_grade /= count_registered;
        printf(";%d;%.2f\n", count_approved, average_grade);
        
    }

    /**
     * Desaloca os alunos e as disciplinas
    */
    linked_list_destroy(students, student_destroy);
    linked_list_destroy(disciplines, discipline_destroy);
    return 0;
}