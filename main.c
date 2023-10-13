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

    char file_name[100];
    printf("Digite o nome do arquivo: ");
    scanf("%[^\n]", file_name);

    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        exit(printf("Erro ao abrir o arquivo"));


    fscanf(f, "\n%d", &number_students);
    /**
     * Lê os dados dos alunos e os insere na lista de alunos
    */
    for (int i = 0; i < number_students; i++) {
        Student *s = student_construct();
        student_read(s, f);
        linked_list_push_front(students, s);
    }


    fscanf(f, "\n%d", &number_disciplines);
    /**
     * Lê os dados das disciplinas e os insere na lista de disciplinas
    */
    for (int i = 0; i < number_disciplines; i++) {
        Discipline *d = discipline_construct();
        discipline_read(d, f);
        linked_list_push_front(disciplines, d);
    }


    fscanf(f, "\n%d", &number_prerequisites);
    /**
     * Busca a disciplina pelo código e a pré-requisito pelo código
     * Em seguida, adiciona a pré-requisito na lista de pré-requisitos da disciplina
    */
    for (int i = 0; i < number_prerequisites; i++) {
        data_type discipline_code[50], prerequisite_code[50];

        fscanf(f, "\n%50[^;];%s", (char*)discipline_code, (char*)prerequisite_code);

        int disc_idx = linked_list_search(disciplines, discipline_code, discipline_verify_code);
        int pre_idx = linked_list_search(disciplines, prerequisite_code, discipline_verify_code);

        if (disc_idx == -1 || pre_idx == -1) 
            continue;
        
        Discipline *d = linked_list_get(disciplines, disc_idx);
        Discipline *p = linked_list_get(disciplines, pre_idx);
        discipline_add_prerequisite(d, p);
    }



    fscanf(f, "\n%d", &number_registrations);
    /**
     * Busca a disciplina pelo código e o aluno pelo número de matrícula
     * Em seguida, registra o aluno em uma das disciplinas da lista
    */
    for (int i = 0; i < number_registrations; i++) {
        data_type discipline_code[50];
        int registration_number;

        fscanf(f, "\n%50[^;];%d;", (char*)discipline_code, &registration_number);

        int disc_idx = linked_list_search(disciplines, discipline_code, discipline_verify_code);
        int stu_idx = linked_list_search(students, &registration_number, student_verify_registration);
        //printf("disc_idx: %d e stu_idx: %d\n", disc_idx, stu_idx);
        if (disc_idx == -1 || stu_idx == -1) {
            //limpar a linha
            char line[100];
            fscanf(f, "%[^\n]", line);
            continue;
        }
        Discipline *d = linked_list_get(disciplines, disc_idx);
        Student *s = linked_list_get(students, stu_idx);
        discipline_register_student(d, s, f);
    }

    fclose(f);

    int report_number;
    printf("Digite o numero do relatorio: ");
    scanf("\n%d", &report_number);
    if(report_number == 1)
        report_1(disciplines);
    else if(report_number == 2)
        report_2(disciplines);
    else if(report_number == 3)
        report_3(disciplines);
    else if(report_number == 4)
        report_4(disciplines, students);
    else if(report_number == 5)
        report_5(disciplines);
    else if(report_number == 6)
        report_6(disciplines, students);
    else if(report_number == 7)
        report_7(disciplines);
    else if(report_number == 8)
        report_8(disciplines);
    else if(report_number == 9)
        report_9(disciplines);
    else if(report_number == 10)
        report_10(disciplines, students);
    else if(report_number == 11)
        report_11(disciplines);
    else if(report_number == 12)
        report_12(disciplines);
    else
        printf("Opcao de relatorio invalido.");

    linked_list_destroy(students, student_destroy);
    linked_list_destroy(disciplines, discipline_destroy);
    return 0;
}