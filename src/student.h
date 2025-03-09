#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>

typedef struct {
    char surname[50];
    char name[50];
    char patronymic[50];
    char gender[10];        // Изменено на строку
    char nationality[50];
    int height;
    int weight;
    int birth_year;
    int birth_month;
    int birth_day;
    char phone[15];
    char postal_code[10];
    char country[50];
    char region[50];
    char district[50];
    char city[50];
    char street[50];
    int house;
    int apartment;
    char school[50];
    int grade;
} Student;

void print_student(Student *s);
int read_student(FILE *input, Student *s, int line_num);
void process_students(FILE *input, FILE *output);

#endif