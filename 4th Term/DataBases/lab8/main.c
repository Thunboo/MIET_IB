#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>
#include <stdbool.h>
 
#define RED             "\x1b[31m"
#define GREEN           "\x1b[32m"
#define YELLOW          "\x1b[33m"
#define BLUE            "\x1b[34m"
#define MAGENTA         "\x1b[35m"
#define CYAN            "\x1b[36m"
#define RESET_COLOR     "\x1b[0m"

char username[64];  // char array for username
PGconn *conn;       // libpq data - connection to DB
char su_check;      // ?


void err_exit(PGconn *conn) 
{
 PQfinish(conn); //Закрытие соединения с сервером базы данных
 exit(1);        //Функция возвращает значение 1 -> программа завершилась аварийно
}
 
void correct_apostrof(char* query) // correcting ' for ` to avoid possible SQL-injection
{
    for(int i = 0; i < strlen(query); ++i)
        if (query[i] == '\'')
            query[i] = '`';
}

/*
*query -> текст запроса
*query_new -> текст запроса после изменения
*/
void add_escape_quotes(char* query, char* query_new)
{
    int j = 0; // length of new edited query

    for(int i = 0; i < strlen(query); ++i) // going through given query
    {
        if(query[i] == '\'')    // ...O'Brien... -> ...O''Brien... <= postgresql apostrof escape sequence
        {
            query_new[j] = '\'';
            query_new[j+1] = '\'';
            j++;                // We added 1 symbol => len of new query is now longer for 1 symbol
        }
        else    query_new[j] = query[i]; // Else - we don't add any new symbols => don't increase total len additional time
        j++;    // Basic len counter
    }
}

bool detect_injection(char* text)
{
    if (strstr(text, "'") != NULL || strstr(text, ";") != NULL) // If there is ' symbol OR if there are no ; symbol
    {                                                           // Then it might be an SQL-injection
        return true;
    }
    return false;
}

/*
Функция печати результата запроса на экран
*conn -> дескриптор подключения к серверу
query -> текст запроса
*/
void print_query(PGconn *conn, PGresult *res)
{
    // Проверка наличия возвращенных запросом строк
    // В случае их отсутствие - аварийное завершение программы
    if (PQresultStatus(res) != PGRES_TUPLES_OK) 
    {
        printf("No data retrieved\n");
        PQclear(res);
        err_exit(conn);
    }

    int rows = PQntuples(res); // Получение числа строк в результате запроса
    int cols = PQnfields(res); // Получение числа столбцов в результате запроса
      
    for(int i=0; i<rows; i++)  // Вывод результата запроса на экран
    {
        for(int j=0; j<cols; j++) 
        {
            printf("%s ", PQgetvalue(res, i, j));
        }
        printf("\n");
    }
    
    if (rows == 0) 
    {
        printf("Zero rows from query\n");
    }

    PQclear(res);
}

/*
    PGconn *conn -> Our connection to DB
    int st_id    -> Student identification number : student_id
    char* f_name -> Field name
*/
void find_students_by_ID(PGconn *conn, int st_id, char* f_name)
{
    // Создаём динамический массив, для помещения в него запроса (размер 512 символов - достаточно)
    char* query = (char*)malloc(512*sizeof(char));

    // Удаление символа окончания строки из введенной фамилии студента
    int pos = strlen(f_name) - 1;
    if (f_name[pos] == '\n')
    f_name[pos]='\0';
    
    // Запрос, возвращающий ФИ, название дисциплины и оценку студента
    // значения st_id и f_name подставляются в запрос
    // на место %d и %s соответственно
    /* 
    sprintf(query, " \
    SELECT LAST_NAME, FIRST_NAME, FIELD_NAME, MARK \
    FROM STUDENTS S \
    JOIN PUBLIC.FIELD_COMPREHENSIONS F_C ON S.STUDENT_ID = F_C.STUDENT_ID \
    JOIN PUBLIC.FIELDS F ON F.FIELD_ID = F_C.FIELD \
    WHERE S.STUDENT_ID = %d AND F.FIELD_NAME = \'%s\'" , st_id, f_name);
    */
    

    if(f_name[0] != '-')    // If Field name is given
        sprintf(query, " \
        SELECT LAST_NAME, FIRST_NAME, FIELD_NAME, MARK \
        FROM STUDENTS S \
        JOIN PUBLIC.FIELD_COMPREHENSIONS F_C ON S.STUDENT_ID = F_C.STUDENT_ID \
        JOIN PUBLIC.FIELDS F ON F.FIELD_ID = F_C.FIELD \
        WHERE S.STUDENT_ID = %d AND FIELD_NAME = \'%s\'" , st_id, f_name);
    else                    // If Field name was not provided : '-'
        sprintf(query, " \
        SELECT LAST_NAME, FIRST_NAME, FIELD_NAME, MARK \
        FROM STUDENTS S \
        JOIN PUBLIC.FIELD_COMPREHENSIONS F_C ON S.STUDENT_ID = F_C.STUDENT_ID \
        JOIN PUBLIC.FIELDS F ON F.FIELD_ID = F_C.FIELD \
        WHERE S.STUDENT_ID = %d AND MARK IS NOT NULL", st_id);
    
    // printf(query);
    // printf("\n");
    PGresult *res = PQexec(conn, query); // Передача запроса на сервер
    print_query(conn, res);
    free(query);
}

/*
Функция поиска информации о студенте из базы
по его номеру студенческого билета и названию дисциплины
с использованием параметрического запроса
*conn -> дескриптор подключения к серверу
st_id -> номер студенческого билета
f_name -> название дисиплины
*/
void find_students_by_ID_Params(PGconn *conn, int st_id, char* f_name)
{
    //Создание массива для задания параметров запроса
    const char *paramValues[2];
    paramValues[0] = (char*) &st_id;
    paramValues[1] = f_name;
    
    char *query = "\
    SELECT LAST_NAME, FIRST_NAME, FIELD_NAME, MARK \
    FROM STUDENTS S \
    JOIN PUBLIC.FIELD_COMPREHENSIONS F_C ON S.STUDENT_ID = F_C.STUDENT_ID \
    JOIN PUBLIC.FIELDS F ON F.FIELD_ID = F_C.FIELD \
    WHERE S.STUDENT_ID=$1 AND F.FIELD_NAME=\'$2\'";

    
    //Вызов параметрического запроса
    PGresult *res = PQexecParams(conn, query, 2, NULL, paramValues, NULL, NULL, 0);
    
    print_query(conn, res);
}

void request_student_marks_with_input(PGconn *conn)
{
    int st_id;
    char field_name[256];

    printf("Enter student ID number: \n");
    scanf("%d", &st_id);
    getchar();

    printf("Enter field name: \n");
    fgets(field_name, 256, stdin);
    int pos = strlen(field_name) - 1;
    if (field_name[pos] == '\n')
    field_name[pos]='\0'; 

    // Фиксим одинарную кавычку если есть
    correct_apostrof(field_name);
    
    if (detect_injection(field_name)) 
    {
        printf(BLUE "SQL-injection was detected\n" RESET_COLOR);
        printf(RED "User, %s, if you'll do it again - you will be banned\n" RESET_COLOR, username);
    }
    else 
    {
        find_students_by_ID(conn, st_id, field_name);
    }
}

PGconn* login() 
{
    char password[64];
    char login_buffer[256];
    int pos;

    printf("Enter username: \n");
    fgets(username, 64, stdin);
    pos = strlen(username) - 1;
    if (username[pos] == '\n')
    username[pos]='\0';

    printf("Enter password: \n");
    fgets(password, 64, stdin);   
    pos = strlen(password) - 1;
    if (password[pos] == '\n')
    password[pos]='\0'; 

    snprintf(login_buffer, sizeof(login_buffer), // ?
    "host=127.0.0.1 user=%s password=%s dbname=students", username, password);

    return PQconnectdb(login_buffer); // ?
}

void relogin() 
{
    if(conn != NULL)
    {
        if (PQstatus(conn) == CONNECTION_OK) // ?
        {
            PQfinish(conn);
        }
    }
    conn = login();

    if (PQstatus(conn) == CONNECTION_BAD) 
    {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        err_exit(conn);
    }
    // ?
    su_check = PQgetvalue(PQexec(conn, "SELECT current_setting('is_superuser') = 'on';"), 0, 0)[0];
}

int check_mark_exists(PGconn *conn, int st_id, const char* field) {
    char query[512];
    sprintf(query,      // ?
            "SELECT mark FROM field_comprehensions fc "
            "JOIN fields f ON f.field_id = fc.field "
            "WHERE student_id = %d AND field_name = '%s'",
            st_id, field);

    PGresult *res = PQexec(conn, query);
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK) 
    {
        PQclear(res);
        return -1;
    }

    int rows = PQntuples(res);
    if (rows == 0) 
    {
        PQclear(res);
        return -1; // Запись не найдена
    }

    int exists = PQgetisnull(res, 0, 0) ? 0 : 1;
    PQclear(res);
    return exists;
}

void update_student_mark(PGconn *conn, int st_id, char* field) {
    int new_mark;

    printf("Введите оценку (1-5): ");
    scanf("%d", &new_mark);
    getchar();

    if (new_mark < 1 || new_mark > 5) 
    {
        printf(RED "Оценка должна быть от 1 до 5\n" RESET_COLOR);
        return;
    }

    char query[512];
    sprintf(query, 
            "UPDATE field_comprehensions fc SET mark = %d "
            "FROM fields f WHERE f.field_id = fc.field AND "
            "student_id = %d AND field_name = \'%s\'", 
            new_mark, st_id, field);

    PGresult *res = PQexec(conn, query);
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
    {
        printf(RED "Ошибка при обновлении оценки: %s\n" RESET_COLOR, PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    printf(GREEN "Оценка успешно обновлена\n" RESET_COLOR);
    PQclear(res);
}

void add_student_mark(PGconn *conn, int st_id, char* field) {
    
    int mark_status = check_mark_exists(conn, st_id, field);
    
    if (mark_status == -1) 
    {
        printf(RED "Ошибка при проверке текущей оценки\n" RESET_COLOR);
        return;
    }
    if (mark_status == 1) 
    {
        printf(RED "У студента уже есть оценка по этому предмету\n" RESET_COLOR);
        return;
    }

    
    int mark;
    printf("Введите оценку (1-5): ");
            scanf("%d", &mark);
            getchar();

    if (mark < 1 || mark > 5) 
    {
        printf(RED "Оценка должна быть от 1 до 5\n" RESET_COLOR);
        return;
    }
    char query[512];
    sprintf(query, 
            "UPDATE field_comprehensions fc SET mark = %d "
            "FROM fields f WHERE f.field_id = fc.field AND "
            "student_id = %d AND field_name = \'%s\'", 
            mark, st_id, field);

    PGresult *res = PQexec(conn, query);
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
    {
        printf(RED "Ошибка при добавлении оценки: %s\n" RESET_COLOR, PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    if (strcmp(PQcmdTuples(res), "0") == 0) 
    {
        printf(YELLOW "Не найдено записи с NULL оценкой или запись не существует\n" RESET_COLOR);
    } else 
    {
        printf(GREEN "Оценка успешно добавлена\n" RESET_COLOR);
    }
    PQclear(res);
}

void delete_student_mark(PGconn *conn, int st_id, char* field) {
    
    int mark_status = check_mark_exists(conn, st_id, field);
    
    if (mark_status == -1) 
    {
        printf(RED "Ошибка при проверке текущей оценки\n" RESET_COLOR);
        return;
    }
    if (mark_status == 0) 
    {
        printf(RED "У студента уже и так нет оценки по этому предмету\n" RESET_COLOR);
        return;
    }
    
    char query[512];
    sprintf(query, 
            "UPDATE field_comprehensions fc SET mark = NULL "
            "FROM fields f WHERE f.field_id = fc.field AND "
            "student_id = %d AND field_name = \'%s\'", 
            st_id, field);

    PGresult *res = PQexec(conn, query);
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
    {
        printf(RED "Ошибка при удалении оценки: %s\n" RESET_COLOR, PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    if (strcmp(PQcmdTuples(res), "0") == 0) 
    {
        printf(YELLOW "Не найдено записи для удаления оценки\n" RESET_COLOR);
    } 
    else 
    {
        printf(GREEN "Оценка успешно удалена (установлена в NULL)\n" RESET_COLOR);
    }
    PQclear(res);
}

void manage_student_marks(PGconn *conn) {
    int choice, st_id;
    char field[64];
    
    printf("Выберите действие:\n"
           "1. Изменить оценку студента\n"
           "2. Добавить оценку студенту (заменить NULL)\n"
           "3. Удалить оценку студента (установить NULL)\n"
           "4. Вернуться назад\n");
    scanf("%d", &choice);
    getchar();
    
    // if (choice == 4) return;
    switch (choice)
    {
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            return;
            break;
        default:
            printf(RED "Неверный выбор\n" RESET_COLOR);
            return;
            break;
    }    

    printf("Введите ID студента: ");
    scanf("%d", &st_id);
    getchar();
    
    printf("Введите название предмета: ");
    fgets(field, 64, stdin);
    int pos = strlen(field) - 1;
    if (field[pos] == '\n')
    field[pos]='\0';
    //printf("\'%s\'\n", field);
    
    switch(choice) {
        case 1:
            update_student_mark(conn, st_id, field);
            break;
        case 2:
            add_student_mark(conn, st_id, field);
            break;
        case 3:
            delete_student_mark(conn, st_id, field);
            break;
        default:
            printf(RED "Неверный выбор\n" RESET_COLOR);
    }
}

void make_choice()
{
    int choice;
    if (su_check == 'f')
    {
        printf(
        "Выберите:\n"
        "1. Вывести 5 случайных студентов\n"
        "2. Запросить оценку студента по предмету\n"
        "3. Зайти под другим пользователем\n"
        "4. Завершить программу\n"
        );
        scanf("%d", &choice);
        getchar();
        switch(choice)
        {
            case 1: 
                PGresult *res = PQexec(conn, "SELECT * FROM students ORDER BY RANDOM() LIMIT 5;");
                print_query(conn, res); break;
            case 2: request_student_marks_with_input(conn); break;
            case 3: relogin(); break;
            case 4: PQfinish(conn); exit(0); break;
            default: printf("Неправильный ввод\n");
        }
    }
    else if (su_check == 't')
    {
        printf(GREEN "Current user is superuser\n" RESET_COLOR);
        printf(
        "Выберите:\n"
        "1. Вывести 5 случайных студентов\n"
        "2. Запросить оценку студента по предмету\n"
        "3. Добавить/Изменить/Удалить оценку у студента\n"
        "4. Зайти под другим пользователем\n"
        "5. Завершить программу\n"
        );
        scanf("%d", &choice);
        getchar();
        switch(choice)
        {
            case 1: 
                PGresult *res = PQexec(conn, "SELECT * FROM students ORDER BY RANDOM() LIMIT 5;");
                print_query(conn, res); break;
            case 2: request_student_marks_with_input(conn); break;
            case 3: manage_student_marks(conn); break;
            case 4: relogin(); break;
            case 5: PQfinish(conn); exit(0); break;
            default: printf("Неправильный ввод\n");
        }
    }
    //make_choice();
}


void main() 
{
    relogin();
    while (1)
    make_choice();
}