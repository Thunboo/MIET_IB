#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>

#define color_output_blue  SetConsoleTextAttribute(hConsole, 3);
#define color_output_green SetConsoleTextAttribute(hConsole, 2);
#define color_output_red   SetConsoleTextAttribute(hConsole, 4);
#define color_output_white SetConsoleTextAttribute(hConsole, 7);

#define clear_out system("CLS");

/*void add_student(struct student* students, int current_size){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //students = (struct student*) realloc(students, (current_size) * sizeof(struct student));
    
    char buffer[100];     int buffer_group;
    students = (struct student*) realloc(students, (current_size) * sizeof(struct student));
    
    printf("Введите фамилию нового студента: ");          color_output_green 
    
    fgets(buffer, sizeof(buffer), stdin); color_output_white
    students[current_size].surname = (char *) malloc(strlen(buffer) + 1);
    strcpy(students[current_size].surname, buffer);
}*/


struct product{
    wchar_t* name;
    wchar_t* name2;
    double cost;
    int amount;
};
void add(struct product** Products, int* size){
    wchar_t buffer[100];
    int buffer_group;
    double lc;
    struct product* temp = realloc(*Products, (*size + 1) * sizeof(struct product));

    if (temp == NULL) {
        // Обработка ошибки выделения памяти
        fprintf(stderr, "Ошибка выделения памяти\n");
        return;
    }

     *Products = temp;

    printf("Name: ");
    fgets(buffer, sizeof(buffer), stdin);
    strcpy(( * Products)[*size].name, buffer);
    // (*Products)[*size].name[sizeof(buffer) - 2] = '\0'; // Удаление символа новой строки
    
    printf("Name2: ");
    fgets(buffer, sizeof(buffer), stdin);
    strcpy(( * Products)[*size].name2, buffer);
    // (*Products)[*size].name2[sizeof(buffer) - 2] = '\0'; // Удаление символа новой строки

    printf("cost : ");
    scanf("%lf", &lc);
    (*Products)[*size].cost = lc;

    printf("amount: ");
    scanf("%d", &buffer_group);
    (*Products)[*size].amount = buffer_group;

    (*size)++;
}

int main(){
    system("cls");
    setlocale(LC_ALL, "");
    // char *locale = setlocale(LC_ALL, "");

    // Date structure
    /*
    struct date{
        int day;
        char month_str[10];
        // int month;
        int year;
    };

    // --------
    struct date birthday;
    birthday.day = 18;
    // birthday.month_str = "december";  // This does not work
    strcpy(birthday.month_str, "december");
    birthday.month = 12;
    birthday.year = 2004;
    printf("%d.%d.%d\n", birthday.month, birthday.day, birthday.year);
    // --------
   
    struct date birthday = {18, "december", 2004};
    printf("%d %s %d\n", birthday.day, birthday.month_str, birthday.year);

    struct date *ptr;
    ptr = &birthday;
    printf("%d %s %d\n", ptr -> day, ptr -> month_str, ptr -> year);
    */
    
    // Product structure
/*
    struct product meat;

    char buffer[100];
    printf("Name : "); fgets(buffer, sizeof(buffer), stdin);
    meat.name = (char *) malloc(strlen(buffer) + 1);
    strcpy(meat.name, buffer); clear_out
    printf("Name2 : "); fgets(buffer, sizeof(buffer), stdin);
    meat.name2 = (char *) malloc(strlen(buffer) + 1);
    strcpy(meat.name2, buffer); clear_out
    printf("Cost : "); scanf("%lf", &meat.cost); clear_out
    printf("Amount : "); scanf("%d", &meat.amount); clear_out

    printf("Product 1:\n Name : %s Name2 : %s Cost : %.2f\n Amount : %d\n", meat.name, meat.name2, meat.cost, meat.amount);
    free(meat.name);
*/
    struct product* Products = (struct product*) malloc(2 * sizeof(struct product));
    Products[0].name = "chicken"; Products[0].name2 = "breasts"; Products[0].cost = 15.2; Products[0].amount = 3;
    Products[1].name = "beef";    Products[1].name2 = "breasts"; Products[1].cost = 15.2; Products[1].amount = 3;
    for (int i = 0; i < 2; i++){
        printf("%s %s %.2f - %d\n", Products[i].name, Products[i].name2, Products[i].cost, Products[i].amount);
    }
    system("pause"); system("cls");
    //*
    Products = (struct product*) realloc(Products, (2 + 1) * sizeof(struct product));
    wchar_t buffer[100];
    printf("Name - ��� : "); fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    for (int i = 0; i < strlen(buffer); i++){
        printf("%d. %c |\n", i, buffer[i]);
    }
    Products[2].name = (char *) malloc(strlen(buffer) + 1);
    strcpy(Products[2].name, buffer); //clear_out
    
    printf("Name2 : "); fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    Products[2].name2 = (char *) malloc(strlen(buffer) + 1);
    strcpy(Products[2].name2, buffer); clear_out

    printf("Cost : "); scanf("%lf", &Products[2].cost); clear_out
    printf("Amount : "); scanf("%d", &Products[2].amount); clear_out
//*/
    // int size_ = 2;
    // add(&Products, &size_);
    for (int i = 0; i < 3; i++){
        printf("%s %s %.2f - %d\n", Products[i].name, Products[i].name2, Products[i].cost, Products[i].amount);
    }
    
    free(Products);
    
    system("pause");
    clear_out
    return 0;
}