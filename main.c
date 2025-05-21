#include <stdio.h>
#include "filesystem.h"
#include <string.h>
#include <stdlib.h>

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



#define MAX_INPUT_LENGTH 256
#define MAX_PARAMS 4

void print_help() {
    printf("Доступные команды:\n");
    printf("создать <имя_файла> - создать новый файл\n");
    printf("удалить <имя_файла> - удалить файл\n");
    printf("изменить <имя_файла> <текст> - изменить содержимое файла\n");
    printf("просмотреть <имя_файла> - показать содержимое файла\n");
    printf("выход - завершить программу\n");
}

void process_command(char* command, char** params, int param_count) {
    if (strcmp(command, "создать") == 0 && param_count == 1) {
        if (create_file(params[0]) == 0) {
            printf("Файл '%s' успешно создан\n", params[0]);
        } else {
            printf("Ошибка при создании файла '%s'\n", params[0]);
        }
    }
    else if (strcmp(command, "удалить") == 0 && param_count == 1) {
        if (delete_file(params[0]) == 0) {
            printf("Файл '%s' успешно удален\n", params[0]);
        } else {
            printf("Ошибка при удалении файла '%s'\n", params[0]);
        }
    }
    else if (strcmp(command, "изменить") == 0 && param_count >= 2) {
        // Объединяем все оставшиеся параметры в текст
        char text[MAX_INPUT_LENGTH] = "";
        for (int i = 1; i < param_count; i++) {
            strcat(text, params[i]);
            if (i < param_count - 1) strcat(text, " ");
        }
        
        if (write_to_file(params[0], text) == 0) {
            printf("Файл '%s' успешно изменен\n", params[0]);
        } else {
            printf("Ошибка при изменении файла '%s'\n", params[0]);
        }
    }
    else if (strcmp(command, "просмотреть") == 0 && param_count == 1) {
        char* content = read_from_file(params[0]);
        if (content != NULL) {
            printf("Содержимое файла '%s':\n%s\n", params[0], content);
            free(content);
        } else {
            printf("Ошибка при чтении файла '%s'\n", params[0]);
        }
    }
    else if (strcmp(command, "помощь") == 0) {
        print_help();
    }
    else {
        printf("Неизвестная команда или неверные параметры. Введите 'помощь' для списка команд\n");
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char* params[MAX_PARAMS];
    char* token;
    
    printf("Добро пожаловать в файловую систему!\n");
    print_help();
    
    while (1) {
        printf("\n> ");
        fgets(input, MAX_INPUT_LENGTH, stdin);
        input[strcspn(input, "\n")] = 0; // Удаляем символ новой строки
        
        if (strcmp(input, "выход") == 0) {
            break;
        }
        
        // Разбиваем ввод на токены
        int param_count = 0;
        token = strtok(input, " ");
        
        while (token != NULL && param_count < MAX_PARAMS) {
            params[param_count++] = token;
            token = strtok(NULL, " ");
        }
        
        if (param_count > 0) {
            process_command(params[0], params + 1, param_count - 1);
        }
    }
    
    printf("Работа с файловой системой завершена\n");
    return 0;
}
