#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define color_output_blue  SetConsoleTextAttribute(hConsole, 3);
#define color_output_green SetConsoleTextAttribute(hConsole, 2);
#define color_output_red   SetConsoleTextAttribute(hConsole, 4);
#define color_output_white SetConsoleTextAttribute(hConsole, 7);

/*
    There is 3 types of memory, that programmm uses:
    1) Static memory - статическая память
        - Хранит глобальные переменные
        - Размер определяется при компиляции
    
    2) Stack         - Стэк
        - Хранит: локальные переменные
                  аргументы функций
                  промежуточные значения вычислений
        - Размер определяется при запуске программы
    
    3) Heap          - Куча
        - Динамически распределяемая память
        - ОС выделяет память по частям (по мере необходимости)
*/

void test_1(){
    int *ptr = (int *) malloc (1000 * sizeof(int));
    // Выделение памяти под 1_000 элементов типа int
    if (ptr == NULL) printf("MEMORY WAS NOT ALLOCATED\n");
    else printf("MEMORY WAS ALLOCATED");
    free (ptr);

    // 2. Выделение (захват памяти)
    
    //void *calloc(size_t nmemb, size_t size);
    // АНАЛОГИЧНО malloc НО!
    // Вместо размера памяти задаём кол-во элементов и размер одного элемента
    // После выполнения память обнуляется
    int *ptr_ = (int *) calloc(1000, sizeof(int));
    // Array of 1000 {0}'s

    // 3. Изменение размера памяти

    // realloc
}

void test_2_1(int n){ // Указатель - локальный объект автоматической памяти
    int *ptr = (int *) calloc(n, sizeof(int));
    //...
    free(ptr);
}
// Выделенная память недоступна при выходе за пределы => надо освободить
void test_2_2(int mode, int N){ // Указатель - локальный объект статической памяти
    time_t current_time;
    srand(time(&current_time));
    static int *ptr;
    int *l_ptr;

    switch (mode){
        case 1:{
            ptr = (int *) calloc(N, sizeof(int));
            break;
        }

        case 2:{
            printf("-- %d -- \n", N);
            for (l_ptr = ptr; l_ptr < ptr + N; l_ptr++){
                *l_ptr = rand() % 100;
            }
            for (l_ptr = ptr; l_ptr < ptr + N; l_ptr++){
                printf("%d \t", *l_ptr);
            }
            break;
        }

        case 3:{
            printf("\n---------\n");
            free(ptr);
            break;
        }
    }
}
// Динамическая память доступна через указатель при повторном входе в блок => освободить
void application_2_2(){
    test_2_2(1, 10);
    test_2_2(2, 10);
    test_2_2(3, 1);
    system("pause");

    test_2_2(1, 50);
    test_2_2(2, 50);
    test_2_2(3, 1);
    system("pause");
}

int *ptr_Global; // Pointer to the dynamic memory (global variable)
void initialize(int size){
    for (int i = i; i < size; i++){
        printf("x[%d] = ", i);
        scanf("%d", &ptr_Global[i]);
    }
}
int summarize(int size){
    int S = 0;
    for (int i = 0; i < size; i++){
        S += ptr_Global[i];
    }
    return S;
}
void test_2_3(){
    int N = 10;
    ptr_Global = (int *) calloc(N, sizeof(int));
    initialize(N);
    printf("\nSum = %d\n", summarize(N));
    free(ptr_Global); ptr_Global = NULL;
    system("pause");
}

/*C++
void new_del(int n){
    int *ptr = new int[n]; // Выделение памяти под N элементов
    int *l_ptr;
    for (l_ptr = ptr; l_ptr < ptr + n; l_ptr++) *l_ptr = rand() % 100;
    for (l_ptr = ptr; l_ptr < ptr + n; l_ptr++) printf("%d\t", *l_ptr);
    delete [] ptr; ptr = NULL;
}
*/

void memory_check(){
    int *ptr; ptr = NULL;
    if (ptr == NULL){ printf("MEMORY WAS NOT ALLOCATED (1)\n"); }
    int N = 1000*1000*1000;// *1000;
    int *ptr2 = (int *) malloc(N * sizeof(int));
    if (ptr2 == NULL){printf("MEMORY WAS NOT ALLOCATED (2)\n"); }
    system("pause");
    free(ptr2);
}

void defining_strings(){
    // C-string : array of type char; ends with '\0'
    char t_s[2]; // 2 symbols including '\0'
    char str1 [5] = "abcdef";
    char *ptr1;
    for (ptr1 = str1; *ptr1 != '\0'; ptr1++){ printf("%c", *ptr1); } printf("\n");
    
    char str2 [] = "abcdef";
    char *ptr2;
    for (ptr2 = str2; *ptr2 != '\0'; ptr2++){ printf("%c", *ptr2); } printf("\n");
}
void defining_text(){
    char text [3][6] = {"Hello", " - ", "world!"};
    // 3 words of max length 6
}
void input_text(int N){
    char text [N][20];
    
    printf("Input few strings oon latin\n(End of input - empty string)\n");
    for (int i = 0; i < N; i++){
        gets(text[i]); // Writing down text (working with first index)
        if (!text[i][0]) break; // text[i][0] == 0 -> empty string
    }

    printf("Inputed text:\n");
    int k;
    for (k = 0; k < N; k++){
        if (!text[k][0]) break;
        else puts(text[k]);
    }
    printf("\n-------------------\n");
    for (int i = 0; i < k; i++){
        for (int j = 0; j < k; j++){
            if (!strcmp(text[i], text[j]) && i != j){
                printf("Same strings: %d = %d\n", i, j);
            }
        }
    }
    printf("\n-------------------\n");
    int i, cnt;
    for (i = 0, cnt = 0; i < k; i++){
        for (int j = 0; text[i][j]; j++){ // While text[i][j] != 0
            if (isdigit(text[i][j])) cnt++;
        }
    }
    printf(" There is %d digits in text\n", cnt);
    system("pause");
}

void dinamic_string(int N){
    char str[N];
    char *din_str;
    // 1) Inputting data into static buffer
    printf("Input string\n"); gets(str);
    // 2) Allocating memory from "Heap"
    din_str = (char *) malloc (strlen(str) + 1);
    printf("Allocated memory was not initialized: %s \n", din_str);
    // 3) Relocating data into dinamic memory
    strcpy(din_str, str);
    printf("\nThis is dinamic string: %s \n", din_str);
    system("pause");
}
void dinamic_input_text(int N){
    char buffer[N]; buffer[0] = '1'; //char buffer[N] = {'1'};
    char *ptr_text[N]; // Static array of pointers for addressing dinamic strings
    char *ptr_str;
    int i, j, k, cnt;
    printf("Input your text:\n");
    for (k = 0; buffer[0]; k++){
        gets(buffer);
        ptr_text[k] = (char *) malloc (strlen(buffer) + 1);
        strcpy(ptr_text[k], buffer);
    }
    printf("\n------------------\n");
    for (i = 0; i + 1 < k; i++){
        for (j = i + 1; j < k; j++){
            if (!strcmp(ptr_text[i], ptr_text[j]) && i != j){
                printf("Same strings: %d and %d\n", i, j);
            }
        }
    }
    printf("\n------------------\n");
    for (i = 0, cnt = 0; i < k; i++){
        //printf("%s\n", ptr_text[i]);
        for (ptr_str = ptr_text[i]; *ptr_str; ptr_str++){
            if (isdigit(*ptr_str)) cnt++;
        }
    }
    printf("There is %d digits in text\n", cnt);
    
    for (i = 0; i < k; i++){
        free(ptr_text[i]);
        ptr_text[i] = NULL;
    }
}

void double_star_input_text(int N){
    char **dpt; // Dinamic array of pointers on dinamic strings
    char *ptr_str;
    char buffer[N]; buffer[0] = '1';
    int i, j, k, cnt;

    // Allocating memory for dinamic array of pointers
    //dpt = (char **) malloc (sizeof(*dpt)*N);
    dpt = (char **) malloc (sizeof(char *) * N);

    // Allocating memory and initialization of dinamic strings
    for (k = 0; buffer[0]; k++){
        gets(buffer);
        dpt[k] = (char *) malloc(strlen(buffer) + 1);
        strcpy(dpt[k], buffer);
    }
    printf("\n------------------\n");
    for (i = 0; i + 1 < k; i++){
        for (j = i + 1; j < k; j++){
            if (!strcmp(dpt[i], dpt[j])){
                printf("Same strings: %d and %d\n", i, j);
            }
        }
    }
    printf("\n------------------\n");
    for (i = 0, cnt = 0; i < k; i++){
        for (ptr_str = dpt[i]; *ptr_str; ptr_str++){
            if (isdigit(*ptr_str)) cnt++;
        }
    }
    printf("There is %d digits in text\n");

    for (i = 0; i < k; i++){
        free(dpt[i]); // Returning memory of dinamic strings
        free(dpt);    // Returning memory of pointers array
    }
}

void string_functions(int N){
    char str_1[N], str_2[N];
    printf("Input your text (1):\n"); gets(str_1); 
    printf("Input your text (2):\n"); gets(str_2); printf("\n");

    printf("First text length: %d\n", strlen(str_1));
    printf("Second text length: %d\n",strlen(str_2)); printf("\n");

    strcmp(str_1, str_2); // = 0 - Strings are equal
                          // > 0 - Str_1 is bigger than Str_2
                          // < 0 - Str_1 is less than Str_2
    strcat(str_1, str_2); // Extends Str_1 with Str_2

    strcpy(str_1, "CONST"); // Rewrites Str_1 with new line

    if (strchr(str_2, '!')){
        printf("There is a '!' in line %s\n", str_2);
        printf("'!' is on position %d\n", strchr(str_2, '!') - str_2);
    }
    else { printf("There is no '!' in line\n"); }

    char S[] = {"part of string"};
    if (strstr(str_2, S)){
        printf("There is %s if string %s\n", S, str_2);
        printf("%s is on %d position\n", S, strstr(str_2, S) - str_2);
    }
}


int summarize_column(int **matrix, int column, int m){
    int i, summ;
    for (i = 0, summ = 0; i < m; i++){
        summ += matrix[i][column];
    }
    return summ;
}
int summarize_row(int **matrix, int row, int n){
    int j, summ;
    for (j = 0, summ = 0; j < n; j++){
        summ += matrix[row][j];
    }
    return summ;
}
void dinamic_matrixes(){
    int **Matrix; // Pointer to dinamic matrix
    int i,j;
    int n = 3, m = 5;
    Matrix = (int **) malloc(sizeof(*Matrix) * n);
    for (i = 0; i < n; i++){
        Matrix[i] = (int *) malloc(sizeof(*Matrix[i]));
        for (j = 0; j < m; j++){
            Matrix[i][j] = rand() % 100;
            printf("%5d", Matrix[i][j]);
        }
        printf(" | %5d", summarize_row(Matrix, i, m));
        printf("\n");
    }
    printf("--------------------------\n");
    for (int column = 0; column < m; column++){
        printf("%5d", summarize_column(Matrix, column, n));
    }
}

int main(){
    system("cls");
    time_t CT; srand(time(&CT));
    //application_2_2();
    //test_2_3();
    //memory_check();
    //defining_strings();
    //input_text(10);
    //dinamic_string (10);
    //dinamic_input_text (100);
    dinamic_matrixes();

    system("pause");

    printf("\n\n");
    system("pause");
    return 0;
}