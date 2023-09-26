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
    LinkedList *registrations = linked_list_construct();

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
        Registration *r = registration_construct();
        registration_read(r);
        linked_list_push_front(registrations, r);

        //Aqui sera interessante buscar o estudante pela matricular e associar ele a disciplina
        //Pelo codigo da disciplina buscar a disiciplina tbm
        //Preciso fazer uma funcao de busca na lista encadeada
    }
    return 0;
}