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

Teacher *teacher_construct(char *name) {
    Teacher *t = (Teacher*)malloc(sizeof(Teacher));
    if (t == NULL)
        exit(printf("Erro ao alocar memoria"));
        
    t->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(t->name, name);
    t->name[strlen(name)] = '\0';
    t->disapprovals = 0;
    return t;
}

void teacher_destroy(data_type data) {
    Teacher *t = (Teacher*)data;
    free(t->name);
    free(t);
}

int teacher_compare_name(data_type data1, data_type data2) {
    Teacher *t1 = (Teacher*)data1;
    Teacher *t2 = (Teacher*)data2;
    if (strcmp(t1->name, t2->name) == 0)
        return 1;
    return 0;
}

int teacher_compare_disapprovals(data_type data1, data_type data2) {
    Teacher *t1 = (Teacher*)data1;
    Teacher *t2 = (Teacher*)data2;
    return t1->disapprovals - t2->disapprovals;
}

void teacher_print(data_type data) {
    Teacher *t = (Teacher*)data;

    printf("%s %d\n", t->name, t->disapprovals);
  

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
    
    if (linked_list_size(prerequisites) > 1)
        prerequisites = linked_list_reverse(prerequisites);
    
    linked_list_print(prerequisites, discipline_print_name);
    linked_list_destroy_node(prerequisites);
}

void report_3(LinkedList *disciplines) {
    char code_dsc[50];
    scanf("\n%[^\n]", code_dsc);
    int idx = linked_list_search(disciplines, code_dsc, discipline_verify_code);
    Discipline *d = linked_list_get(disciplines, idx);
    LinkedList *full_prerequisites = discipline_get_full_prerequisites(d);
    
    if (linked_list_size(full_prerequisites) > 1)
        full_prerequisites = linked_list_reverse(full_prerequisites);

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
        Teacher *t = teacher_construct(teacher);
        linked_list_push_front(teachers, t);
    }
    linked_list_unique(teachers, teacher_compare_name, teacher_destroy);

    for (int i = 0; i < linked_list_size(teachers); i++) {
        Teacher *t = linked_list_get(teachers, i);
        for (int j = 0; j < linked_list_size(disciplines); j++) {
            Discipline *d = linked_list_get(disciplines, j);
            if (strcmp(t->name, discipline_get_teacher(d)) == 0) {
                t->disapprovals += discipline_get_disapprovals(d);
            }
        }
    }

    linked_list_sort(teachers, teacher_compare_disapprovals);
    linked_list_print(teachers, teacher_print);
    linked_list_destroy(teachers, teacher_destroy);

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
    //printf("Total de ocorrencias com pre requisitos nao cursados: ");
    printf("%d\n", count_prerequisites_nr);
}

void report_9(LinkedList *disciplines) {
    int count_prerequisites_disapproved = 0;
    for (int i = 0; i < linked_list_size(disciplines); i++) {
        Discipline *d = linked_list_get(disciplines, i);
        count_prerequisites_disapproved += discipline_check_prerequisites_disapproved(d);
    }
    //printf("Total de ocorrencias com pre requisitos nao aprovados: ");
    printf("%d\n", count_prerequisites_disapproved);
}

void report_10(LinkedList *disciplines, LinkedList *students) {
    if (linked_list_size(students) > 1)
        linked_list_sort(students, student_compare_name);
    
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
    if (linked_list_size(disciplines) > 1)
        linked_list_sort(disciplines, discipline_compare_approval_percentage);
    
    for (int i = 0; i < linked_list_size(disciplines); i++) {
        Discipline *d = linked_list_get(disciplines, i);
        discipline_print_statistics(d);
    }

}

void report_12(LinkedList *disciplines, LinkedList *students) {
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

    for(int i = linked_list_size(students) - 1; i >= 0; i--) {
        Student *s = linked_list_get(students, i);
        student_print_all_data(s);
    }
    printf("\n");

    for (int i = linked_list_size(disciplines) - 1; i >= 0; i--) {
        Discipline *d = linked_list_get(disciplines, i);
        discipline_print_name_and_teacher(d);
    }
    printf("\n");

    for (int i = 0; i < linked_list_size(disciplines); i++) {
        Discipline *d = linked_list_get(disciplines, i);
        LinkedList *prerequisites = discipline_get_direct_prerequisites(d);
        
        for (int j = 0; j < linked_list_size(prerequisites); j++) {
            Discipline *p = linked_list_get(prerequisites, j);
            printf("%s;%s\n", d->code, p->code);
        }
        linked_list_destroy_node(prerequisites);
    }

    printf("\n");

    for (int i = 0; i < linked_list_size(disciplines); i++) {
        Discipline *d = linked_list_get(disciplines, i);
        LinkedList *registrations = discipline_get_registrations(d);
        for (int j = linked_list_size(registrations) - 1; j >= 0; j--) {
            Registration *r = linked_list_get(registrations, j);
            //<código da disciplina>;<matrícula do aluno>;<nota>;<presenças>;<aprovado: 0 ou 1>
            printf("%s;%d;%d;%.1f;%d\n", d->code, registration_get_registration_number(r), (int)registration_get_grade(r), registration_get_presence_percentage(r), registration_get_status(r));
        }
    }
}