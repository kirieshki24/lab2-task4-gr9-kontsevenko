#include "student.h"
#include <stdio.h>

int main() {
    // Открытие входного файла
    FILE *input = fopen("data/students.txt", "r");
    if (!input) {
        perror("\nОшибка открытия students.txt");
        printf("Проверьте:\n- Существование файла\n- Права доступа\n- Правильность пути\n");
        return 1;
    }

    // Создание выходного файла
    FILE *output = fopen("data/output.txt", "w");
    if (!output) {
        perror("\nОшибка создания output.txt");
        fclose(input);
        return 1;
    }

    // Обработка данных
    process_students(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    // Вывод содержимого output.txt в консоль
    printf("\n====== Содержимое output.txt ======\n");
    output = fopen("data/output.txt", "r");
    if (output) {
        int c;
        while ((c = fgetc(output)) != EOF) {
            putchar(c);
        }
        fclose(output);
    } else {
        perror("Ошибка чтения output.txt");
    }

    return 0;
}