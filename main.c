#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "discipline.h"
#include "registration.h"
#include "student.h"


int main() {
    int number_students = 0, number_disciplines = 0, number_registrations = 0;
    LinkedList *students = linked_list_construct();
    LinkedList *disciplines = linked_list_construct();

    scanf("\n%d", &number_students);
    for (int i = 0; i < number_students; i++) {
        Student *s = student_construct();
        student_read(s);
        linked_list_push_front(students, s);
    }

    scanf("\n%d", &number_disciplines);
    for (int i = 0; i < number_disciplines; i++) {
        Discipline *d = discipline_construct();
        discipline_read(d);
        linked_list_push_front(disciplines, d);

        //Falta fazer a leitura dos pre requisitos
    }

    scanf("\n%d", &number_registrations);
    for (int i = 0; i < number_registrations; i++) {
        char discipline_code[50];
        int registration_number;
        scanf("\n%[^;];%d,", discipline_code, &registration_number);


        int disc_idx = linked_list_search(disciplines, &discipline_code, discipline_compare_code);
        Discipline *d = linked_list_get(disciplines, disc_idx);

        int stu_idx = linked_list_search(students, &registration_number, student_compare_registration);
        Student *s = linked_list_get(students, stu_idx);

        discipline_register_student(d, s);
    }
    return 0;
}