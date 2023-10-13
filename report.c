#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "discipline.h"
#include "registration.h"
#include "student.h"

typedef struct Teacher {
    char *name;
    int disapprovals;
} Teacher;

int string_compare(data_type data1, data_type data2) {
    char *s1 = ( char*)data1;
    char *s2 = ( char*)data2;
    if (strcmp(s1, s2) == 0)
        return 1;
    else
        return 0;
}

int int_compare(data_type data1, data_type data2) {
    int *i1 = (int*)data1;
    int *i2 = (int*)data2;
    return *i1 - *i2;
}

void int_print(data_type data) {
    int *i = (int*)data;
    printf("%d", *i);
}

void string_print(data_type data) {
    char *s = (char*)data;
    printf("%s: ", s);
}

void report_1(LinkedList *disciplines) {
    char code_dsc[50];
    scanf("\n%[^\n]", code_dsc);
    int idx = linked_list_search(disciplines, code_dsc, discipline_verify_code);
    Discipline *d = linked_list_get(disciplines, idx);
    discipline_show_students(d);
}

void report_2(LinkedList *disciplines) {
    char code_dsc[50];
    scanf("\n%[^\n]", code_dsc);
    int idx = linked_list_search(disciplines, code_dsc, discipline_verify_code);
    Discipline *d = linked_list_get(disciplines, idx);
    LinkedList *prerequisites = discipline_get_direct_prerequisites(d);
    linked_list_print(prerequisites, discipline_print_name);
    linked_list_destroy_node(prerequisites);
}

void report_3(LinkedList *disciplines) {
    char code_dsc[50];
    scanf("\n%[^\n]", code_dsc);
    int idx = linked_list_search(disciplines, code_dsc, discipline_verify_code);
    Discipline *d = linked_list_get(disciplines, idx);
    LinkedList *full_prerequisites = discipline_get_full_prerequisites(d);
    linked_list_print(full_prerequisites, discipline_print_name);
    linked_list_destroy_node(full_prerequisites);
}

void report_4(LinkedList *disciplines, LinkedList *students) {
    int registration_std = 0;
    scanf("\n%d", &registration_std);
    int idx_r = linked_list_search(students, &registration_std, student_verify_registration);
    Student *s = linked_list_get(students, idx_r);
    LinkedList *registrations_student = linked_list_construct();
    for (int i = 0; i < linked_list_size(disciplines); i++) {
        Discipline *d = linked_list_get(disciplines, i);

        if (discipline_has_registration(d, s)) {
            linked_list_push_front(registrations_student, d);
        }
    }
    //remover disciplinas repetidas
    linked_list_unique(registrations_student, discipline_compare_code, discipline_destroy);
    linked_list_print(registrations_student, discipline_print_name);
    linked_list_destroy_node(registrations_student);
}

void report_5(LinkedList *disciplines) {
    LinkedList *teachers = linked_list_construct();
    for (int i = 0; i < linked_list_size(disciplines); i++) {
        Discipline *d = linked_list_get(disciplines, i);
        char *teacher = discipline_get_teacher(d);
        linked_list_push_front(teachers, teacher);
    }

    linked_list_unique(teachers, string_compare, NULL);

    LinkedList *disapprovals = linked_list_construct();
    for (int i = 0; i < linked_list_size(teachers); i++) {
        char *teacher = linked_list_get(teachers, i);
        int *count = (int*)calloc(1, sizeof(int));
        for (int j = 0; j < linked_list_size(disciplines); j++) {
            Discipline *d = linked_list_get(disciplines, j);
            if (strcmp(teacher, discipline_get_teacher(d)) == 0) {
                *count += discipline_get_disapprovals(d);
            }
        }
        linked_list_push_front(disapprovals, count);
        //free(count);
    }

    //Ordenar as duas listas de acordo com o número de disapprovals
    //linked_list_sort_pair(disapprovals, teachers, int_compare);
    linked_list_print_pair(teachers, disapprovals, string_print, int_print);
  
    linked_list_destroy(disapprovals, free);
    linked_list_destroy_node(teachers);
}

void report_6(LinkedList *disciplines, LinkedList *students) {
    int registration_std = 0;
    scanf("\n%d", &registration_std);
    int idx_r = linked_list_search(students, &registration_std, student_verify_registration);
    Student *s = linked_list_get(students, idx_r);
    LinkedList *disc_appvd = linked_list_construct();
    for (int i = 0; i < linked_list_size(disciplines); i++) {
        Discipline *d = linked_list_get(disciplines, i);
        if (discipline_is_approved(d, s)) {
            linked_list_push_front(disc_appvd, d);
        }
    }
    linked_list_sort(disc_appvd, discipline_compare_name);
    linked_list_print(disc_appvd, discipline_print_name);
    linked_list_destroy_node(disc_appvd);
}

void report_7(LinkedList *disciplines) {
    for (int i = 0; i < linked_list_size(disciplines); i++) {
        Discipline *d = linked_list_get(disciplines, i);
        discipline_check_inconsistency(d);
    }
}

void report_8(LinkedList *disciplines) {
    int count_prerequisites_nr = 0;
    for (int i = 0; i < linked_list_size(disciplines); i++) {
        Discipline *d = linked_list_get(disciplines, i);
        count_prerequisites_nr += discipline_check_prerequisites(d);
    }
    printf("Total de ocorrencias com pre requisitos nao cursados: %d\n", count_prerequisites_nr);
}

void report_9(LinkedList *disciplines) {
    int count_prerequisites_disapproved = 0;
    for (int i = 0; i < linked_list_size(disciplines); i++) {
        Discipline *d = linked_list_get(disciplines, i);
        count_prerequisites_disapproved += discipline_check_prerequisites_disapproved(d);
    }
    printf("Total de ocorrencias com pre requisitos nao aprovados: %d\n", count_prerequisites_disapproved);
}

void report_10(LinkedList *disciplines, LinkedList *students) {
    for (int i = 0; i < linked_list_size(students); i++) {
        Student *s = linked_list_get(students, i);
        printf("Nome: ");
        student_print_name(s);
        printf("Numero de matricula: ");
        student_print_registration_number(s);
    
        int count_approved = 0, count_registered = 0;
        float average_grade = 0;
        //Verificar a quantidade de disciplinas que o aluno foi aprovado
        for (int j = 0; j < linked_list_size(disciplines); j++) {
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
        printf("\nTotal disciplinas aprovadas: %d\n", count_approved);
        printf("Total disciplinas cursadas: %d\n", count_registered);
        printf("Nota media nas disciplinas: %.2f\n", average_grade);
        printf("\n");

    }

}

void report_11(LinkedList *disciplines) {
    linked_list_sort(disciplines, discipline_compare_approval_percentage);
    for (int i = 0; i < linked_list_size(disciplines); i++) {
        Discipline *d = linked_list_get(disciplines, i);
        discipline_print_statistics(d);
    }

}

void report_12(LinkedList *disciplines) {
    data_type discipline_code[50];
    scanf("\n%[^\n]", (char*)discipline_code);
    int disc_idx = linked_list_search(disciplines, discipline_code, discipline_verify_code);
    if (disc_idx != -1) {
        Discipline *d = linked_list_get(disciplines, disc_idx);

        //Remover de todos os prerequisitos
        for (int i = 0; i < linked_list_size(disciplines); i++) {
            Discipline *p = linked_list_get(disciplines, i);
            linked_list_remove(p->prerequisites, d, NULL);
        }
        linked_list_remove(disciplines, d, discipline_destroy);
    }
}