#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>
#include "RU_CL_console.h"

#define color_output_blue  SetConsoleTextAttribute(hConsole, 3);
#define color_output_green SetConsoleTextAttribute(hConsole, 2);
#define color_output_red   SetConsoleTextAttribute(hConsole, 4);
#define color_output_white SetConsoleTextAttribute(hConsole, 7);
#define SEPARATOR printf("-----------------------------------------------\n");
#define CLEAR_ system("cls");
#define PAUSE_ system("pause");
#define SIZE_OF_DATABASE 8

struct student {
        char* surname;
        char* name;
        int group;
    };

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
            students[i].surname = (char *) malloc(sizeof(Surnames_female[id_surname]) + 1);
            strcpy(students[i].surname, Surnames_female[id_surname]);
            students[i].name    = (char *) malloc(sizeof(      Names_female[id_name]) + 1);
            strcpy(students[i].name, Names_female[id_surname]);
        }  
        else {
            students[i].surname = (char *) malloc(sizeof(Surnames_male[id_surname]) + 1);
            strcpy(students[i].surname, Surnames_male[id_surname]);
            students[i].name    = (char *) malloc(sizeof(      Names_male[id_name]) + 1);
            strcpy(students[i].name, Names_male[id_surname]);
        }   
    }
}
void print_database(){
    CLEAR_
    printf("БАЗА ДАННЫХ - Студенты\n"); SEPARATOR
    for (int i = 0; i < current_size; i++){
        printf("| %14s | %12s | ГРУППА № %2d |\n", students[i].surname, students[i].name, students[i].group);
    }
    SEPARATOR PAUSE_ CLEAR_
}
void clear_memory(){
    free(students);
}
void add(){
    struct student new_student;
    char new_name[24], new_surname[24];
    getchar();
    printf("Введите:\nФамилию > ");  gets(new_surname); new_student.surname = (char *) malloc(sizeof(new_surname) + 1); strcpy(new_student.surname, new_surname); //new_student.surname = new_surname;
    printf("Имя > ");                gets(new_name);    new_student.name    = (char *) malloc(sizeof(new_name)    + 1); strcpy(new_student.name,    new_name);    //new_student.name    = new_name;
    printf("Номер группы > ");       scanf("%d", &new_student.group);
    if (current_size == max_size){
        max_size *= 2;
        students = realloc(students, max_size * sizeof(struct student));
    }
    students[current_size] = new_student;
    current_size++;
}
void sort_database(){
    struct student temp;
    for (int i = 0; i < current_size; i++){
        for (int j = 0; j < current_size; j++){
            if (strcmp(students[i].surname, students[j].surname) < 0){
                temp.surname = (char *) malloc(sizeof(students[i].surname) + 1);
                strcpy(temp.surname, students[i].surname);
                temp.name = (char *) malloc(sizeof(students[i].name) + 1);
                strcpy(temp.name,    students[i].name);
                temp.group = students[i].group;

                strcpy(students[i].surname, students[j].surname);
                strcpy(students[i].name,    students[j].name);
                students[i].group = students[j].group;

                strcpy(students[j].surname, temp.surname);
                strcpy(students[j].name, temp.name);
                students[j].group = temp.group;
            
                free(temp.surname);
                free(temp.name);
            }
        }
    }
}
void find_from_group(){
    CLEAR_
    int group_;
    printf("Введите номер группы, студентов которой будем искать: ");
    scanf("%d", &group_); CLEAR_
    printf("Студенты группы №%d :\n", group_); SEPARATOR
    for (int i = 0; i < current_size; i++){
        if (students[i].group == group_){
            printf("| %14s | %12s |\n", students[i].surname, students[i].name);
        }
    }
    SEPARATOR PAUSE_ CLEAR_
}
void search_(){
    CLEAR_
    char selection = '0';
    char name_[24], surname_[24];
    int found_cnt = 0;
    while ((selection != '1') && (selection != '2') && (selection != '3') && (selection != '4')){
        printf("Введите тип поиска:\n-------------------\n1. По фамилии\n2. По имени\n3. По фамилии и имени\n4. Выйти в меню\n-------------------\n");
        selection = getchar(); CLEAR_
    }
    getchar();
    switch(selection){
        case '1':
            printf("Введите Фамилию > ");    gets(surname_); CLEAR_

            printf("Найденные студенты с фамилией %14s :\n", surname_); SEPARATOR
            for (int i = 0; i < current_size; i++){
                if (strstr(surname_, students[i].surname)){
                    if(strlen(surname_) == strlen(students[i].surname)){ found_cnt++;
                        printf("| %14s | %12s | ГРУППА № %2d |\n", students[i].surname, students[i].name, students[i].group);
                     }
                }
            } 
            break;
        case '2':
            printf("Введите Имя > ");        gets(name_); CLEAR_

            printf("Найденные студенты с именем %12s :\n", name_); SEPARATOR
            for (int i = 0; i < current_size; i++){
                if (strstr(name_, students[i].name)){
                    if(strlen(name_) == strlen(students[i].name)){ found_cnt++;
                        printf("| %14s | %12s | ГРУППА № %2d |\n", students[i].surname, students[i].name, students[i].group);
                     }
                }
            } 
            break;
        case '3':
            printf("Введите:\nФамилию > ");  gets(surname_);
            printf("\nИмя > ");              gets(name_); CLEAR_

            printf("Найденные студенты с фамилией %14s и именем %12s :\n", surname_, name_); SEPARATOR
            for (int i = 0; i < current_size; i++){
                if (strstr(surname_, students[i].surname)){
                    if(strlen(surname_) == strlen(students[i].surname)){ 
                        if (strstr(name_, students[i].name)){
                            if(strlen(name_) == strlen(students[i].name)){ found_cnt++;
                                printf("| %14s | %12s | ГРУППА № %2d |\n", students[i].surname, students[i].name, students[i].group);
                            }
                        }
                    }
                }
            } 
            break;
        case '4':
            break;
    }
    if (selection == '1' || '2' || '3'){
        if (found_cnt > 0) SEPARATOR
        else printf("Не было найдено студентов по такому запросу... \n\n");
    }
    if (selection != '4') PAUSE_ 
    CLEAR_
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
            case 1:
                add();
                break;
            case 2:
                print_database();
                break;
            case 3:
                search_();
                break;
            case 4:
                find_from_group();
                break;
            case 5:
                sort_database();
                break;
            case 6:
                MENU = 0;
                clear_memory(students);
                CLEAR_ 
                color_output_red printf("ЗАКРЫВАЕМ ПРОГРАММУ."); sleep(1); printf("."); sleep(1); printf("."); sleep(1);
                break;
            case 11: printf("%d\n", current_size); PAUSE_ break;
            default:
                break;
        }   
    }
    return 0;
}