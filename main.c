#include <stdio.h>
#include "filesystem.h"

int main() {
    const char* filename = "test.txt";
    const char* data = "Hello, File System!";
    
    // Создаем файл
    if (create_file(filename) == 0) {
        printf("Файл успешно создан\n");
    } else {
        printf("Ошибка при создании файла\n");
        return -1;
    }
    
    // Записываем данные
    if (write_to_file(filename, data) == 0) {
        printf("Данные успешно записаны\n");
    } else {
        printf("Ошибка при записи данных\n");
        return -1;
    }
    
    // Читаем данные
    char* content = read_from_file(filename);
    if (content != NULL) {
        printf("Содержимое файла: %s\n", content);
        free(content);
    } else {
        printf("Ошибка при чтении файла\n");
        return -1;
    }
    
    return 0;
}
