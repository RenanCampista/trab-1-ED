#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "discipline.h"
#include "registration.h"
#include "student.h"
#include "report.h"

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

    report_1(disciplines);
    report_2(disciplines);
    report_3(disciplines);
    report_4(disciplines, students);
    report_5(disciplines);
    report_6(disciplines, students);
    report_7(disciplines);
    report_8(disciplines);
    report_9(disciplines);
    report_10(disciplines, students);
    report_11(disciplines);
    report_12(disciplines);

    linked_list_destroy(students, student_destroy);
    linked_list_destroy(disciplines, discipline_destroy);
    return 0;
}