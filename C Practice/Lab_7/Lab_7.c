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
#define MAIN_MENU_SEPARATOR printf("-----------------------------------------------\n");
#define SEPARATOR printf("------------------------------------------------------------------------------------\n");
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
int current_size, max_size; // SIZE_OF_DATABASE, SIZE_OF_DATABASE * 2;

void main_menu(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    MAIN_MENU_SEPARATOR
    printf("| "); color_output_blue printf("Добавить ещё одного студента ............ 1 "); color_output_white printf("|\n");
    printf("| "); color_output_blue printf("Вывести базу данных студентов ........... 2 "); color_output_white printf("|\n");
    printf("| "); color_output_blue printf("Поиск студента по имени/фамилии ......... 3 "); color_output_white printf("|\n");
    printf("| "); color_output_blue printf("Сортировать БД  ......................... 4 "); color_output_white printf("|\n");
    MAIN_MENU_SEPARATOR
    printf("| "); color_output_blue printf("Сформировать случайную базу данных  ..... 5 "); color_output_white printf("|\n");
    printf("| "); color_output_blue printf("Записать базу данных в файл ............. 6 "); color_output_white printf("|\n");
    printf("| "); color_output_blue printf("Считать базу данных с файла ............. 7 "); color_output_white printf("|\n");
    printf("| "); color_output_blue printf("Закрыть программу  ...................... 8 "); color_output_white printf("|\n");
    MAIN_MENU_SEPARATOR color_output_blue printf("  Выберете опцию (введите номер)\n"); color_output_green
}

void form_database(int SIZE_FOR_DATABASE){
    char Surnames_male[50][12] = {"Smirnov", "Ivanov", "Kuzneczov", "Sokolov", "Popov", "Lebedev", "Kozlov", "Novikov", "Morozov", "Petrov", "Volkov", 
                                  "Solovyov", "Vasilev", "Zaiyczev", "Pavlov", "Semyonov", "Golubev", "Vinogradov", "Bogdanov", "Vorobyov", "Fyodorov", 
                                  "Mixaiylov", "Belyaev", "Tarasov", "Belov", "Komarov", "Orlov", "Kiselyov", "Makarov", "Andreev", "Kovalyov", 
                                  "Ilin", "Gusev", "Titov", "Kuzmin", "Kudryavcev", "Baranov", "Kulikov", "Alekseev", "Stepanov", "Yakovlev", 
                                  "Sorokin", "Sergeev", "Romanov", "Zaxarov", "Borisov", "Korolyov", "Gerasimov", "Ponomaryov", "Grigorev"};
    char Surnames_female[50][12] = {"Smirnova", "Ivanova", "Kuzneczova", "Sokolova", "Popova", "Lebedeva", "Kozlova", "Novikova", "Morozova", "Petrova", "Volkova", 
                                    "Solovyova", "Vasileva", "Zaiyczeva", "Pavlova", "Semyonova", "Golubeva", "Vinogradova", "Bogdanova", "Vorobyova", "Fyodorova", 
                                    "Mixaiylova", "Belyaeva", "Tarasova", "Belova", "Komarova", "Orlova", "Kiselyova", "Makarova", "Andreeva", "Kovalyova", 
                                    "Ilina", "Guseva", "Titova", "Kuzmina", "Kudryavceva", "Baranova", "Kulikova", "Alekseeva", "Stepanova", "Yakovleva", 
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
    char Patr_female[50][20] = {"Aleksandrovna", "Alekseevna", "Anatolevna", "Andreevna", "Antonovna", "Arkadevna", "Artemovna", "Bogdanovna", 
                                "Borisovna", "Valentinovna", "Valerevna", "Vasilevna", "Viktorovna", "Vitalievna", "Vladimirovna", "Vladislavovna",
                                "Vyacheslavovna", "Gennadievna", "Georgievna", "Grigorevna", "Danilovna", "Denisovna", "Dmitrievna", "Evgenevna", 
                                "Egorovna", "Efimovna", "Ivanovna", "Iosifovna", "Kirillovna", "Konstantinovna", "Filippovna", "Eduardovna",
                                "Leonidovna", "Lvovna", "Maksimovna", "Matveevna", "Mixailovna", "Nikolaevna", "Olegovna", "Pavlovna", 
                                "Petrovna", "Platonovna", "Robertovna", "Romanovna", "Semenovna", "Sergeevna", "Stanislavovna", "Stepanovna", 
                                "Timofeevna", "Fedorovna"};
    char Patr_male[50][20] = {"Aleksandrovich", "Alekseevich", "Anatolevich", "Andreevich", "Antonovich", "Arkadevich", "Artemovich", "Bedrosovich", 
                              "Bogdanovich", "Borisovich", "Valentinovich", "Valerevich", "Vasilevich", "Viktorovich", "Vitalevich", "Vladimirovich", 
                              "Vladislavovich", "Volfovich", "Vyacheslavovich", "Gennadievich", "Georgievich", "Grigorevich", "Danilovich", "Denisovich", 
                              "Dmitrievich", "Evgenevich", "Egorovich", "Efimovich", "Ivanovich", "Ivanych", "Ignatevich", "Igorevich", 
                              "Ilich", "Iosifovich", "Isaakovich", "Kirillovich", "Konstantinovich", "Leonidovich", "Lvovich", "Maksimovich", 
                              "Matveevich", "Mixailovich", "Nikolaevich", "Olegovich", "Pavlovich", "Palych", "Petrovich", "Platonovich", 
                              "Robertovich", "Romanovich"};
    int id_surname, id_name, id_patr;

    if (SIZE_FOR_DATABASE <= 3) { current_size = SIZE_OF_DATABASE; printf("Введено значение <= 3 !\nИспользовано базовое количество студенстов = 8\n"); PAUSE_} 
    else {current_size = SIZE_FOR_DATABASE; } 
    max_size = current_size * 2; 

    students = (struct student*) malloc(max_size * sizeof(struct student));

    for (int i = 0; i < current_size; i++){
        students[i].group = i % (current_size / 4) + 1;
        id_surname = rand() % 50;
        id_name = rand() % 50;
        id_patr = rand() % 50;
        if (rand() % 2) {
            students[i].FIO.surname = (char *) malloc(sizeof(Surnames_female[id_surname]) + 1);
            strcpy(students[i].FIO.surname, Surnames_female[id_surname]);
            students[i].FIO.name    = (char *) malloc(sizeof(      Names_female[id_name]) + 1);
            strcpy(students[i].FIO.name, Names_female[id_surname]);
            students[i].FIO.fname   = (char *) malloc(sizeof(       Patr_female[id_patr]) + 1);
            strcpy(students[i].FIO.fname, Patr_female[id_patr]);
        }  
        else {
            students[i].FIO.surname = (char *) malloc(sizeof(Surnames_male[id_surname]) + 1);
            strcpy(students[i].FIO.surname, Surnames_male[id_surname]);
            students[i].FIO.name    = (char *) malloc(sizeof(      Names_male[id_name]) + 1);
            strcpy(students[i].FIO.name, Names_male[id_surname]);
            students[i].FIO.fname   = (char *) malloc(sizeof(       Patr_male[id_patr]) + 1);
            strcpy(students[i].FIO.fname, Patr_male[id_patr]);
        }
        students[i].birthdate.year = 2024 - 18 - (rand() % 10);
        int month = rand() % 12 + 1;
        students[i].birthdate.month = month;
        int day;
        switch (month){
            case 1:  // Jan
            case 3:  // Mar
            case 5:  // May
            case 7:  // Jul
            case 8:  // Aug
            case 10: // Okt
            case 12: // Dec
                day = rand() % 31 + 1;
                break;
            case 4:  // Apr
            case 6:  // Jun
            case 9:  // Sep
            case 11: // Nov
                day = rand() % 30 + 1;
                break;
            case 2: // Feb
                if (students[i].birthdate.year % 4 == 0){
                    day = rand() % 29 + 1;
                }
                else {
                    day = rand() % 28 + 1;
                }
        }
        students[i].birthdate.day = day;
    }
}

void print_student(int id){
    printf("| %14s | %12s | %16s | ГРУППА № %2d | BD: %2d %3s %4d |\n", 
                students[id].FIO.surname,   students[id].FIO.name,        students[id].FIO.fname, 
                students[id].group,
                students[id].birthdate.day, months[students[id].birthdate.month - 1], students[id].birthdate.year);
}
void print_database(){
    CLEAR_
    printf("БАЗА ДАННЫХ - Студенты\n"); SEPARATOR 
    for (int id = 0; id < current_size; id++){
        print_student(id);
    }
    if (current_size == 0) { printf("База данных ещё не заполнена !\n"); }
    SEPARATOR PAUSE_ CLEAR_
}
void write_database(char * File_Name){
    if (_access(File_Name, 0) == 0){
        FILE * File_Pointer = fopen(File_Name, "w");
    
        for (int id = 0; id < current_size; id++){
            printf("ЗАПИСЫВАЕМ ДАННЫЕ ... %d / %d\n", id + 1, current_size);
            fprintf(File_Pointer, "|%s|%s|%s|%d|%d|%d|%d|\n", 
                students[id].FIO.surname,   students[id].FIO.name,        students[id].FIO.fname, 
                students[id].group,
                students[id].birthdate.day, students[id].birthdate.month, students[id].birthdate.year);
        }
        fclose(File_Pointer);
    }
    printf("ДАННЫЕ УСПЕШНО ЗАПИСАНЫ !\n");
    PAUSE_
}
void read_database(char * File_Name){
    if (_access(File_Name, 0) == 0){        
        current_size = 0; max_size = 1;
        students = (struct student*) malloc(sizeof(struct student) * max_size);

        FILE * File_Pointer = fopen(File_Name, "r");
    
        char buffer_line[200];
        char * token;
        char * date_token;
        int cnt1 = 0, cnt2 = 0;
        int id = 0;
        while (fgets(buffer_line, 200, File_Pointer)){
            if (current_size == max_size){
                max_size *= 2;
                students = realloc(students, sizeof(struct student) * max_size);
            }
            // Записываем фамилию
            token = strtok(buffer_line, "|");
            students[id].FIO.surname = (char *) malloc(sizeof(token) + 1);
            strcpy(students[id].FIO.surname, token);

            // Записываем имя
            token = strtok(NULL, "|");
            students[id].FIO.name = (char *) malloc(sizeof(token) + 1);
            strcpy(students[id].FIO.name, token);
            
            // Записываем отчество
            token = strtok(NULL, "|");
            students[id].FIO.fname = (char *) malloc(sizeof(token) + 1);
            strcpy(students[id].FIO.fname, token);
            
            // Записываем номер группы
            token = strtok(NULL, "|");
            students[id].group = atoi(token);
            
            // Записываем дату рождения
            token = strtok(NULL, "|");
            students[id].birthdate.day   = atoi(token);
            token = strtok(NULL, "|");
            students[id].birthdate.month = atoi(token);
            token = strtok(NULL, "|");
            students[id].birthdate.year  = atoi(token);

            id++;
            current_size++;
        }
        printf("ДАННЫЕ УСПЕШНО ПРОЧИТАНЫ !\n");
        fclose(File_Pointer);
        PAUSE_
    }
}

void clear_memory(){
    for (int id = 0; id < current_size; id++){
        free(students[id].FIO.surname);
        free(students[id].FIO.name);
        free(students[id].FIO.fname);
    }
    free(students);
}

void add_student(){
    struct student new_student;
    char new_surname[14], new_name[12], new_fname[16];
    getchar();
    printf("Введите:\nФамилию > ");  gets(new_surname); new_student.FIO.surname = (char *) malloc(sizeof(new_surname) + 1); strcpy(new_student.FIO.surname, new_surname);
    printf("Имя > ");                gets(new_name);    new_student.FIO.name    = (char *) malloc(sizeof(new_name)    + 1); strcpy(new_student.FIO.name,    new_name);
    printf("Отчество > ");           gets(new_fname);   new_student.FIO.fname   = (char *) malloc(sizeof(new_fname)   + 1); strcpy(new_student.FIO.fname,   new_fname);
    printf("Номер группы > ");       scanf("%d", &new_student.group);
    printf("Дату рождения:\n");
    printf("День > ");               scanf("%d", &new_student.birthdate.day);
    printf("Месяц > ");              scanf("%d", &new_student.birthdate.month);
    printf("Год > ");                scanf("%d", &new_student.birthdate.year);
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
            if (strcmp(students[i].FIO.surname, students[j].FIO.surname) < 0){
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

void find_from_group(int* found_cnt){
    CLEAR_
    int group_;
    printf("Введите номер группы, студентов которой будем искать: ");
    scanf("%d", &group_); CLEAR_
    printf("Студенты группы №%d :\n", group_); SEPARATOR
    for (int id = 0; id < current_size; id++){
        if (students[id].group == group_){
            *found_cnt += 1;
            print_student(id);
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
    for (int id = 0; id < current_size; id++){
        if (strstr(surname_buffer, students[id].FIO.surname)){
            if(strlen(surname_buffer) == strlen(students[id].FIO.surname)){ 
                *found_cnt += 1;
                print_student(id);
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
    for (int id = 0; id < current_size; id++){
        if (strstr(name_buffer, students[id].FIO.name)){
            if(strlen(name_buffer) == strlen(students[id].FIO.name)){ 
                *found_cnt += 1;
                print_student(id);
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
    for (int id = 0; id < current_size; id++){
        if (strstr(surname_buffer, students[id].FIO.surname)){
            if(strlen(surname_buffer) == strlen(students[id].FIO.surname)){ 
                if (strstr(name_buffer, students[id].FIO.name)){
                    if(strlen(name_buffer) == strlen(students[id].FIO.name)){ 
                        *found_cnt += 1;
                        print_student(id);
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
    for (int id = 0; id < current_size; id++){
        if (strstr(fname_buffer, students[id].FIO.fname)){
            if(strlen(fname_buffer) == strlen(students[id].FIO.fname)){ 
                *found_cnt += 1;
                print_student(id);
            }
        }
    } 
    if (*found_cnt != 0) SEPARATOR PAUSE_ CLEAR_
}
void find_by_age(int* found_cnt){
    CLEAR_
    time(&rawtime);
    timeinfo = localtime(&rawtime);   // СОХРАНЯЕМ ТЕКУЩЕЕ ВРЕМЯ
    char age_buffer[20] = "buffer";
    int age_finding;
    struct date TODAY;                // СОЗДАЁМ СТРУКТУРУ ДАННЫХ ТИПА - DATE -> ЗАПИСЫВАЕМ ТЕКУЩУЮ ДАТУ
    TODAY.day = timeinfo->tm_mday, TODAY.month = timeinfo->tm_mon, TODAY.year = timeinfo->tm_year + 1900;
    printf("Сегодня > %d:%d:%d\n", TODAY.day, TODAY.month, TODAY.year);
    getchar();

    while (!(atoi(age_buffer)) || (atoi(age_buffer) <= 0)){   // ПОКА ПОЛЬЗОВАТЕЛЬ НЕ ВВЕЛ ЧИСЛО ИЛИ ВВЕЛ ЧИСЛО <= 0
        printf("Введите возраст, старше которого будет производится поиск студентов > ");  gets(age_buffer);   CLEAR_
    }
    age_finding = atoi(age_buffer);
    printf("Найденные студенты старше %d :\n", age_finding); SEPARATOR

    for (int id = 0; id < current_size; id++){
        if (students[id].birthdate.year < TODAY.year - age_finding){ // ПО ГОДУ СРАЗУ ВИДНО, ЧТО СТАРШЕ
                    *found_cnt += 1;
                    print_student(id);                     
        }
        else if (students[id].birthdate.year == TODAY.year - age_finding){ // СОВПАЛ ГОД
            if (students[id].birthdate.month < TODAY.month){               // СОВПАЛ ГОД, НО МЕСЯЦ УДОВЛЕТВОРЯЕТ УСЛОВИЮ => НЕ ПРОВЕРЯЕМ ДЕНЬ
                    *found_cnt += 1;
                    print_student(id);                    
            }
            else if (students[id].birthdate.month == TODAY.month){ // СОВПАЛ ГОД И МЕСЯЦ
                if (students[id].birthdate.day <= TODAY.day){      // ТОГДА ПРОВЕРКА ПО ДНЮ
                    *found_cnt += 1;
                    print_student(id);                    
                }
            }
        }
    }
         
    if (*found_cnt != 0) SEPARATOR PAUSE_ CLEAR_
}

void search(){
    int inMenu1 = 1, inMenu2 = 1;
    int found_cnt = 0, was_finding = 0;
    char Menu_Option_1 = '0', Menu_Option_2 = '0';

    while (inMenu1){
        CLEAR_  SEPARATOR
        printf("Введите тип поиска:\n");
        printf("1. ФИО\n2. Возраст\n3. Номер группы\n4. Вернуться в главное меню\n");
        Menu_Option_1 = getchar();

        switch(Menu_Option_1){
            case '1':   // ПОИСК ПО ФИО
                inMenu2 = 1;
                while (inMenu2){
                    CLEAR_
                    SEPARATOR
                    printf("Уточните тип поиска:\n");
                    printf("1. По фамилии\n2. По имени\n3. По фамилии и имени\n4. По отчеству\n5. На предыдущий пункт\n");
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
            case '2':   // ПОИСК ПО ВОЗРАСТУ
                find_by_age(&found_cnt);
                inMenu1 = 0;
                break;
            case '3':   // ПОИСК ПО НОМЕРУ ГРУППЫ
                find_from_group(&found_cnt);
                inMenu1 = 0;
                break;
            case '4':   // ВЫХОД В ГЛАВНОЕ МЕНЮ
                inMenu1 = 0;
                break;
            default:
                break;
        }
        
        // СМОТРИМ, БЫЛ ЛИ ПРОИЗВЕДЕН ПОИСК
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
        if (was_finding == 1 && found_cnt == 0){ // ЕСЛИ ИСКАЛИ И НЕ НАШЛИ
            printf("Не было найдено студентов по такому запросу... \n\n");
            PAUSE_
        }
    }
}

int main(){
    time_t CT; srand(time(&CT));  
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    enable_colors(); set_utf_8();

    int option = -1, MENU = 1;
    char *file_name = "DB_Lab_7.txt";

    while (MENU){
        CLEAR_
        main_menu();
        scanf("%d", &option); color_output_white
        
        switch (option){
            case 1:     // Добавить студента
                add_student();
                break;
            case 2:     // Вывести базу данных
                print_database();
                break;
            case 3:     // Поиск студента по базе данных
                search();
                break;
            case 4:     // Сортировать базу данных по фамилиям студентов
                sort_database();
                break;
        //--------------------------------------------------------------
            case 5:     // Сгенерировать базу данных из студентов
                int input;
                clear_memory();
                CLEAR_ color_output_blue printf("Введите сколько сгенерировать студентов в базу данных:\n! Минимально - 3\n"); 
                color_output_green scanf("%d", &input); color_output_white
                form_database(input);
                break; 
            case 6:     // Записать базу данных из студентов в файл
                write_database(file_name);
                break;
            case 7:     // Считать базу данных из студентов из файла
                clear_memory();
                read_database(file_name);
                break;
            case 8:
                MENU = 0;
                clear_memory();
                CLEAR_  color_output_red 
                printf("ЗАКРЫВАЕМ ПРОГРАММУ."); sleep(1); printf("."); sleep(1); printf("."); sleep(1);
                color_output_white
                break;
            case 9:     
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                printf("Время сейчас : %d.%d.%d - %d:%d:%d\n", 
                        timeinfo->tm_hour, timeinfo->tm_min,     timeinfo->tm_sec, 
                        timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
                PAUSE_
                break;
            default:
                break;
        }   
    }
    return 0;
}