#ifndef _REPORT_H
#define _REPORT_H
#include "linked_list.h"

/**
 * Lê o código de uma disciplina e mostra os nomes dos alunos que possuem matrícula na disciplina, um por linha, e sem repetição.
*/
void report_1(LinkedList *disciplines);

/**
 * Lê o código de uma disciplina e mostra os nomes das disciplinas que são pré-requisitos, um por linha. Os dados devem ser exibidos na ordem em que são dados no arquivo de entrada.
*/
void report_2(LinkedList *disciplines);

/**
 * Lê o código de uma disciplina e mostra os nomes da cadeia completa de pré-requisitos.
*/
void report_3(LinkedList *disciplines);

/**
 * Lê o número de matrícula de um aluno e mostra a lista de disciplinas que o aluno possui matrícula, sem repetição. 
*/
void report_4(LinkedList *disciplines, LinkedList *students);

/**
 * Para cada professor, mostra na tela o seu nome e o número de reprovações em disciplinas que ele ministrou. Os dados são apresentados de forma ordenada do maior número de reprovações para o menor.
*/
void report_5(LinkedList *disciplines);

/**
 * Lê o número de matrícula de um aluno e mostra na tela a lista de disciplinas em que ele foi aprovado (status = 1 ou (nota final >= 5 e percentual de aprovação >= 75%)). Os dados são apresentados de forma ordenada pelo nome da disciplina, em ordem alfabética. 
*/
void report_6(LinkedList *disciplines, LinkedList *students);

/**
 * Por um erro no sistema, em algumas matrículas, o status de aprovação está inconsistente com os valores de nota final e percentual de presença. Mostra na tela a lista de linhas inconsistentes no mesmo formato do arquivo. 
*/
void report_7(LinkedList *disciplines);

/**
 * Por um um erro no sistema, alguns alunos foram matriculados em disciplinas sem ter cursado os pré-requisitos. Mostra na tela o número de matrículas em que isto aconteceu.
*/
void report_8(LinkedList *disciplines);

/**
 * Por um erro no sistema, alguns alunos cursaram os pré-requisitos, mas não foram aprovados, e mesmo assim foram capazes de se matricular em uma disciplina. Mostra na tela o número de matrículas em que esta inconsistência aconteceu.
*/
void report_9(LinkedList *disciplines);

/**
 * Para cada aluno, mostra o nome do aluno, o número de matrícula, o número de disciplinas em que ele foi aprovado, o número de disciplinas cursadas e a nota média nas disciplinas. Exibe os dados de forma ordenada pelo nome do aluno, em ordem alfabética. 
*/
void report_10(LinkedList *disciplines, LinkedList *students);

/**
 * Para cada disciplina, mostra na tela o código da disciplina, seu nome, o nome do professor da disciplina, o número de matrículas, o número de aprovações e a nota média dos alunos. Exiba os dados de forma ordenada pelo percentual de aprovações, do maior para o menor.  
*/
void report_11(LinkedList *disciplines);

/**
 * Lê o código de uma disciplina e remove todas as menções à disciplina nas estruturas de dados. Em seguida, mostra na tela qual seria o conteúdo do arquivo de entrada após a remoção da disciplina.
*/
void report_12(LinkedList *disciplines, LinkedList *students);




#endif