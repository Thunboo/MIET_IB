#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>
#include "RU_CL_console.h"

// Добавить генерацию отчеств       => malloc
// Добавить генерацию даты рождения => malloc
// Добавить проверку возраста
// Добавить поиск по отчеству
// Дополнить сортировку изменением отчества и даты рождения

#define color_output_blue  SetConsoleTextAttribute(hConsole, 3);
#define color_output_green SetConsoleTextAttribute(hConsole, 2);
#define color_output_red   SetConsoleTextAttribute(hConsole, 4);
#define color_output_white SetConsoleTextAttribute(hConsole, 7);
#define SEPARATOR printf("-----------------------------------------------\n");
#define CLEAR_ system("cls");
#define PAUSE_ system("pause");
#define SIZE_OF_DATABASE 8

struct fio {
        char* surname;
        char* name;
        char* fname;
    };

struct date {
        int day;
        int month;
        int year;
    };

struct student {
        struct fio FIO;
        struct date birthdate;
        int group;
    };

char * months[12] = {"Jan", "Feb", "Mar", "Apr", 
                     "May", "Jun", "Jul", "Aug", 
                     "Sep", "Okt", "Nov", "Dec"};

time_t rawtime;
struct tm * timeinfo;

struct student *students;
int current_size = SIZE_OF_DATABASE, max_size = SIZE_OF_DATABASE * 2;

void main_menu(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SEPARATOR
    printf("| "); color_output_blue printf("Добавить ещё одного студента ............ 1 "); color_output_white printf("|\n");
    printf("| "); color_output_blue printf("Вывести базу данных студентов ........... 2 "); color_output_white printf("|\n");
    printf("| "); color_output_blue printf("Поиск студента по имени/фамилии ......... 3 "); color_output_white printf("|\n");
    printf("| "); color_output_blue printf("Вывести всех студентов из группы № Х .... 4 "); color_output_white printf("|\n");
    printf("| "); color_output_blue printf("Сортировать БД  ......................... 5 "); color_output_white printf("|\n");
    printf("| "); color_output_blue printf("Закрыть программу  ...................... 6 "); color_output_white printf("|\n");
    SEPARATOR color_output_blue printf("  Выберете опцию (введите номер)\n"); color_output_green
}
void form_database(){
    char Surnames_male[50][12] = {"Smirnov", "Ivanov", "Kuzneczov", "Sokolov", "Popov", "Lebedev", "Kozlov", "Novikov", "Morozov", "Petrov", "Volkov", 
                                "Solovyov", "Vasilev", "Zaiyczev", "Pavlov", "Semyonov", "Golubev", "Vinogradov", "Bogdanov", "Vorobyov", "Fyodorov", 
                                "Mixaiylov", "Belyaev", "Tarasov", "Belov", "Komarov", "Orlov", "Kiselyov", "Makarov", "Andreev", "Kovalyov", 
                                "Ilin", "Gusev", "Titov", "Kuzmin", "Kudryavczev", "Baranov", "Kulikov", "Alekseev", "Stepanov", "Yakovlev", 
                                "Sorokin", "Sergeev", "Romanov", "Zaxarov", "Borisov", "Korolyov", "Gerasimov", "Ponomaryov", "Grigorev"};
    char Surnames_female[50][12] = {"Smirnova", "Ivanova", "Kuzneczova", "Sokolova", "Popova", "Lebedeva", "Kozlova", "Novikova", "Morozova", "Petrova", "Volkova", 
                                "Solovyova", "Vasileva", "Zaiyczeva", "Pavlova", "Semyonova", "Golubeva", "Vinogradova", "Bogdanova", "Vorobyova", "Fyodorova", 
                                "Mixaiylova", "Belyaeva", "Tarasova", "Belova", "Komarova", "Orlova", "Kiselyova", "Makarova", "Andreeva", "Kovalyova", 
                                "Ilina", "Guseva", "Titova", "Kuzmina", "Kudryavczeva", "Baranova", "Kulikova", "Alekseeva", "Stepanova", "Yakovleva", 
                                "Sorokina", "Sergeeva", "Romanova", "Zaxarova", "Borisova", "Korolyova", "Gerasimova", "Ponomaryova", "Grigoreva"};
    char Names_female[50][12] = {"Anastasiya", "Anna", "Mariya", "Elena", "Darya", "Alina", "Irina", "Ekaterina", "Arina", "Polina", "Olga", 
                                "Yuliya", "Tatyana", "Natalya", "Viktoriya", "Elizaveta", "Kseniya", "Milana", "Veronika", "Alisa", "Valeriya", 
                                "Aleksandra", "Ulyana", "Kristina", "Sofiya", "Marina", "Svetlana", "Varvara", "Sofya", "Diana", "Yana", 
                                "Kira", "Angelina", "Margarita", "Eva", "Alyona", "Darina", "Karina", "Vasilisa", "Olesya", "Adelina", 
                                "Oksana", "Taisiya", "Nadezhda", "Evgeniya", "Elina", "Zlata", "Eseniya", "Milena", "Vera"};
    char Names_male[50][12] = {"Aleksandr", "Dmitriy", "Maksim", "Sergey", "Andrey", "Aleksey", "Artyom", "Ilya", "Kirill", "Mixail", "Nikita", 
                                "Matvey", "Roman", "Egor", "Arseniy", "Ivan", "Denis", "Evgeniy", "Daniil", "Timofey", "Vladislav", 
                                "Igor", "Vladimir", "Pavel", "Ruslan", "Mark", "Konstantin", "Timur", "Oleg", "YAroslav", "Anton", 
                                "Nikolay", "Gleb", "Danil", "Saveliy", "Vadim", "Stepan", "Yuriy", "Bogdan", "Artur", "Semen", 
                                "Makar", "Lev", "Viktor", "Elisey", "Vitaliy", "Vyacheslav", "Zaxar", "Miron", "Damir"};

    int id_surname, id_name;
    for (int i = 0; i < SIZE_OF_DATABASE; i++){
        students[i].group = i % (SIZE_OF_DATABASE / 4) + 1;
        id_surname = rand() % 50;
        id_name = rand() % 50;
        if (rand() % 2) {
            students[i].FIO.surname = (char *) malloc(sizeof(Surnames_female[id_surname]) + 1);
            strcpy(students[i].FIO.surname, Surnames_female[id_surname]);
            students[i].FIO.name    = (char *) malloc(sizeof(      Names_female[id_name]) + 1);
            strcpy(students[i].FIO.name, Names_female[id_surname]);
        }  
        else {
            students[i].FIO.surname = (char *) malloc(sizeof(Surnames_male[id_surname]) + 1);
            strcpy(students[i].FIO.surname, Surnames_male[id_surname]);
            students[i].FIO.name    = (char *) malloc(sizeof(      Names_male[id_name]) + 1);
            strcpy(students[i].FIO.name, Names_male[id_surname]);
        }
        students[i].birthdate.year = 2024 - 16 - (rand() % 10);
        int month = rand() % 12 + 1;
        students[i].birthdate.month = month;
        int day;
        switch (month){
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                day = rand() % 31;
                break;
            case 4: 
            case 6:
            case 9:
            case 11:
                day = rand() % 30;
                break;
            case 2:
                if (students[i].birthdate.year % 4 == 0){
                    day = rand() % 29;
                }
                else {
                    day = rand() % 28;
                }
        }
    }
}
void print_database(){
    CLEAR_
    printf("БАЗА ДАННЫХ - Студенты\n"); SEPARATOR
    for (int i = 0; i < current_size; i++){
        printf("| %14s | %12s | ГРУППА № %2d |\n", students[i].FIO.surname, students[i].FIO.name, students[i].group);
    }
    SEPARATOR PAUSE_ CLEAR_
}
void clear_memory(){
    free(students);
}

void find_from_group(int* found_cnt){
    CLEAR_
    int group_;
    printf("Введите номер группы, студентов которой будем искать: ");
    scanf("%d", &group_); CLEAR_
    printf("Студенты группы №%d :\n", group_); SEPARATOR
    for (int i = 0; i < current_size; i++){
        if (students[i].group == group_){
            *found_cnt += 1;
            printf("| %14s | %12s |\n", students[i].FIO.surname, students[i].FIO.name);
        }
    }
    if (*found_cnt != 0) {SEPARATOR PAUSE_ CLEAR_}
}
void find_by_surname(int* found_cnt){
    CLEAR_
    char surname_buffer[24];
    getchar();
    printf("Введите Фамилию > ");    gets(surname_buffer); CLEAR_

    printf("Найденные студенты с фамилией %14s :\n", surname_buffer); SEPARATOR
    for (int i = 0; i < current_size; i++){
        if (strstr(surname_buffer, students[i].FIO.surname)){
            if(strlen(surname_buffer) == strlen(students[i].FIO.surname)){ 
                *found_cnt += 1;
                printf("| %14s | %12s | ГРУППА № %2d |\n", students[i].FIO.surname, students[i].FIO.name, students[i].group);
            }
        }
    } 
    if (*found_cnt != 0) {SEPARATOR PAUSE_ CLEAR_}
}
void find_by_name(int* found_cnt){
    CLEAR_
    char name_buffer[24];
    getchar();
    printf("Введите Имя > ");        gets(name_buffer); CLEAR_

    printf("Найденные студенты с именем %12s :\n", name_buffer); SEPARATOR
    for (int i = 0; i < current_size; i++){
        if (strstr(name_buffer, students[i].FIO.name)){
            if(strlen(name_buffer) == strlen(students[i].FIO.name)){ 
                *found_cnt += 1;
                printf("| %14s | %12s | ГРУППА № %2d |\n", students[i].FIO.surname, students[i].FIO.name, students[i].group);
            }
        }
    } 
    if (*found_cnt != 0) {SEPARATOR PAUSE_ CLEAR_}
}
void find_by_both(int* found_cnt){
    CLEAR_
    char name_buffer[24], surname_buffer[24];
    getchar();
    printf("Введите:\nФамилию > ");  gets(surname_buffer);
    printf("\nИмя > ");              gets(name_buffer);    CLEAR_

    printf("Найденные студенты с фамилией %14s и именем %12s :\n", surname_buffer, name_buffer); SEPARATOR
    for (int i = 0; i < current_size; i++){
        if (strstr(surname_buffer, students[i].FIO.surname)){
            if(strlen(surname_buffer) == strlen(students[i].FIO.surname)){ 
                if (strstr(name_buffer, students[i].FIO.name)){
                    if(strlen(name_buffer) == strlen(students[i].FIO.name)){ 
                        *found_cnt += 1;
                        printf("| %14s | %12s | ГРУППА № %2d |\n", students[i].FIO.surname, students[i].FIO.name, students[i].group);
                    }
                }
            }
        }
    } 
    if (*found_cnt != 0) {SEPARATOR PAUSE_ CLEAR_}
}
void find_by_fname(int* found_cnt){
    CLEAR_
    char fname_buffer[24];
    getchar();
    printf("Введите Отчество > ");        gets(fname_buffer); CLEAR_

    printf("Найденные студенты с отчеством %12s :\n", fname_buffer); SEPARATOR
    for (int i = 0; i < current_size; i++){
        if (strstr(fname_buffer, students[i].FIO.fname)){
            if(strlen(fname_buffer) == strlen(students[i].FIO.fname)){ 
                *found_cnt += 1;
                printf("| %14s | %12s | %12s | ГРУППА № %2d |\n", students[i].FIO.surname, students[i].FIO.name, students[i].FIO.fname, students[i].group);
            }
        }
    } 
    if (*found_cnt != 0) SEPARATOR PAUSE_ CLEAR_
}
void search2(){
    int inMenu1 = 1, inMenu2 = 1;
    char Menu_Option_1 = '0', Menu_Option_2 = '0';
    int found_cnt = 0, age = 0;

    while (inMenu1){
        CLEAR_
        SEPARATOR
        printf("Choose search type:\n");
        printf("1. FIO\n2. Age\n3. Group\n4. Back to menu\n");
        Menu_Option_1 = getchar();

        switch(Menu_Option_1){
            case '1':
                inMenu2 = 1;
                while (inMenu2){
                    CLEAR_
                    SEPARATOR
                    printf("Specify seatch type:\n");
                    printf("1. Surname\n2. Name\n3. Both\n4. Other\n5. Back to menu\n");
                    Menu_Option_2 = getchar();
                    
                    switch(Menu_Option_2){
                        case '1':
                            find_by_surname(&found_cnt);
                            inMenu1 = 0; inMenu2 = 0;
                            break;
                        case '2':
                            find_by_name(&found_cnt);
                            inMenu1 = 0; inMenu2 = 0;
                            break;
                        case '3':
                            find_by_both(&found_cnt);
                            inMenu1 = 0; inMenu2 = 0;
                            break;
                        case '4':
                            find_by_fname(&found_cnt);
                            inMenu1 = 0; inMenu2 = 0;
                            break;
                        case '5':
                            inMenu2 = 0;
                            break;
                    }
                }
                break;
            case '2':
                printf("age search...\n"); PAUSE_
                inMenu1 = 0;
                break;
            case '3':
                find_from_group(&found_cnt);
                inMenu1 = 0;
                break;
            case '4':
                inMenu1 = 0;
                break;
            default:
                break;
        }
        
        int was_finding = 0;
        switch(Menu_Option_1){
            case '2':
            case '3':
                was_finding = 1;
                break;
            default:
                break;
        }
        switch(Menu_Option_2){
            case '1':
            case '2':
            case '3':
            case '4':
                was_finding = 1;
                break;
            default:
                break;
        }
        if (was_finding == 1 && found_cnt == 0){
            printf("Не было найдено студентов по такому запросу... \n\n");
            PAUSE_
        }
    }
}

int main(){
    time_t CT; srand(time(&CT));  
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    enable_colors(); set_utf_8();

    students = (struct student*) malloc(max_size * sizeof(struct student));
    form_database();
    int option = -1, MENU = 1;

    while (MENU){
        CLEAR_
        main_menu(option);
        scanf("%d", &option); color_output_white
        switch (option){
            case 2:
                print_database();
                break;
            case 3:
                search2();
                break;
            case 6:
                MENU = 0;
                clear_memory(students);
                CLEAR_  color_output_red 
                printf("ЗАКРЫВАЕМ ПРОГРАММУ."); sleep(1); printf("."); sleep(1); printf("."); sleep(1);
                color_output_white
                break;
            default:
                break;
        }   
    }
    return 0;
}