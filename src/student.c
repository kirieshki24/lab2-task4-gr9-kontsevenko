#include "student.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void print_student(Student *s) {
    printf("\n=== Студент ===\n");
    printf("ФИО:    %s %s %s\n", s->surname, s->name, s->patronymic);
    printf("Пол:    %s | Нац.: %s\n", s->gender, s->nationality);  // Изменено на %s
    printf("Рост/Вес: %d см / %d кг\n", s->height, s->weight);
    printf("Дата рождения: %04d-%02d-%02d\n", 
          s->birth_year, s->birth_month, s->birth_day);
    printf("Телефон: %s\n", s->phone);
    printf("Адрес:   %s, %s, %s\n", s->postal_code, s->country, s->region);
    printf("          %s, %s, ул. %s, %d-%d\n", 
          s->district, s->city, s->street, s->house, s->apartment);
    printf("Школа:   %s, %d класс\n", s->school, s->grade);
    printf("========================\n");
}

int read_student(FILE *input, Student *s, int line_num) {
    memset(s, 0, sizeof(Student));
    char buffer[1024];
    
    if (!fgets(buffer, sizeof(buffer), input)) {
        return feof(input) ? -1 : 0;
    }

    buffer[strcspn(buffer, "\r\n")] = 0;

    int parsed = sscanf(buffer,
        "%49[^;];%49[^;];%49[^;];%9[^;];%49[^;];%d;%d;%d;%d;%d;"  // Изменено %c -> %9[^;]
        "%14[^;];%9[^;];%49[^;];%49[^;];%49[^;];%49[^;];"
        "%49[^;];%d;%d;%49[^;];%d",
        s->surname, 
        s->name, 
        s->patronymic, 
        s->gender,      // Теперь считываем строку
        s->nationality,
        &s->height, 
        &s->weight, 
        &s->birth_year, 
        &s->birth_month, 
        &s->birth_day,
        s->phone, 
        s->postal_code, 
        s->country, 
        s->region, 
        s->district,
        s->city, 
        s->street, 
        &s->house, 
        &s->apartment, 
        s->school, 
        &s->grade);

    if (parsed != 21) {
        fprintf(stderr, "\nОШИБКА в строке %d:\n", line_num);
        fprintf(stderr, "Получено %d/21 полей\nСтрока: %s\n", parsed, buffer);
        return 0;
    }
    return 1;
}

void process_students(FILE *input, FILE *output) {
    Student s;
    int line = 1, total = 0, valid = 0, fifth_grade = 0;

    printf("\n====== Обработка данных ======\n");
    
    while (1) {
        int res = read_student(input, &s, line);
        if (res == -1) break;
        
        if (res == 1) {
            print_student(&s);
            total++;
            valid++;
            
            if (s.grade == 5) {
                fprintf(output, "%s;%s;%s;%s;%s;%d;%d;%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%d;%d;%s;%d\n",  // Изменено %c -> %s
                    s.surname, 
                    s.name, 
                    s.patronymic, 
                    s.gender,     // Теперь выводим строку
                    s.nationality,
                    s.height, 
                    s.weight, 
                    s.birth_year, 
                    s.birth_month, 
                    s.birth_day,
                    s.phone, 
                    s.postal_code, 
                    s.country, 
                    s.region, 
                    s.district,
                    s.city, 
                    s.street, 
                    s.house, 
                    s.apartment, 
                    s.school, 
                    s.grade);
                fifth_grade++;
            }
        } else {
            total++;
        }
        line++;
    }

    printf("\n====== Результаты ======\n");
    printf("Всего строк:        %d\n", total);
    printf("Корректных записей: %d\n", valid);
    printf("Учеников 5 класса:  %d\n", fifth_grade);
    printf("Ошибок формата:    %d\n", total - valid);
}