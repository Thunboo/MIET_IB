#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define color_output_blue  SetConsoleTextAttribute(hConsole, 3);
#define color_output_green SetConsoleTextAttribute(hConsole, 2);
#define color_output_red   SetConsoleTextAttribute(hConsole, 4);
#define color_output_white SetConsoleTextAttribute(hConsole, 7);

int words_counter(char* sentence){
    int cnt = 0, len = strlen(sentence);
    char lastChar;
    if ( len > 0 ){ lastChar = sentence[0]; }
    for (int i = 0; i <= len; i++){
        if ( (sentence[i] == ' ' || sentence[i] == '\0') && lastChar != ' '){
            cnt++;
        }
        lastChar = sentence[i];
    }
    return cnt;
}
int digit_counter(char* sentence){
    int cnt = 0;
    for (int i = 0; i < strlen(sentence); i++){
        if (isdigit(sentence[i])) cnt++;
    }
    return cnt;
}
int space_counter(char* sentence){
    int cnt = 0;
    for (int i = 0; i < strlen(sentence); i++){
        if (sentence[i] == ' ') cnt++;
    }
    return cnt;
}
int csymb_counter(char* sentence){
    // counts up special symbols
    int cnt = 0;
    for (int i = 0; i < strlen(sentence); i++){
        if (iscntrl(sentence[i])) cnt++;
    }  
    return cnt;
}

void text(int N){
    char **dpt; 
    char *ptr_str;
    char buffer[N]; buffer[0] = '1';
    
    int i, j, k, cnt;
    
    int amount_of_strings = 0, words_cnt = 0;
    char and_str[] = {"and"};
    char *dinamic_buffer;
    int flag = 1; 

    dpt = (char **) malloc (sizeof(char *) * N);
    for (k = 0; flag; k++){
        gets(buffer);
        dpt[k] = (char *) malloc(strlen(buffer) + 1);
        strcpy(dpt[k], buffer);
        amount_of_strings++;
        if (strstr(dpt[k], and_str)){
            if(strlen(dpt[k]) == strlen(and_str)) flag = 0; amount_of_strings--;
        }
    }
    dpt[amount_of_strings] = NULL;
    
    int results [amount_of_strings][4];
    int temp [4] = {0};
    for (k = 0; k < amount_of_strings; k++){
        results[k][0] = words_counter(dpt[k]);
        results[k][1] = digit_counter(dpt[k]);
        results[k][2] = space_counter(dpt[k]);
        results[k][3] = csymb_counter(dpt[k]);
    }

    for (j = 0; j < amount_of_strings; j++){
        for (i = 0; i < amount_of_strings - 1; i++){
            if (results[i][0] > results[i + 1][0]){
                //printf("1) %s : %d\n2) %s : %d\n-----\n", dpt[i], results[i][0], dpt[i+1], results[i+1][0]);
                dinamic_buffer = (char *) malloc(strlen(dpt[i] + 1));
                for (k = 0; k < 4; k++) { temp[k] = results[i][k]; }
                strcpy(dinamic_buffer, dpt[i]);
                for (k = 0; k < 4; k++) { results[i][k] = results[i + 1][k]; }
                strcpy(dpt[i], dpt[i + 1]);
                for (k = 0; k < 4; k++) { results[i + 1][k] = temp[k]; }
                strcpy(dpt[i + 1], dinamic_buffer);
                free(dinamic_buffer);
            }
        }
    }
    system("cls");
    for (i = 1; i < amount_of_strings; i++){
        printf("%s\nwords : %d | digits : %d | spaces : %d | special chars : %d\n\n", dpt[i], results[i][0], results[i][1], results[i][2], results[i][3]);
    }
    for (i = 0; i < k; i++){
        free(dpt[i]); // Returning memory of dinamic strings
        free(dpt);    // Returning memory of pointers array
    }
}

double summarize_column(double **matrix, int column, int start, int end){
    int i; double summ;
    for (i = start, summ = 0; i < end; i++){
        summ += matrix[i][column];
    }
    return summ;
}
double summarize_row(double **matrix, int row, int start, int end){
    int j; double summ;
    for (j = start, summ = 0; j < end; j++){
        summ += matrix[row][j];
    }
    return summ;
}
void dinamic_matrixes(int n, int m){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    double **Matrix; // Pointer to dinamic matrix
    int i,j;
    int start, end;
    int flag = 0;
    // Matrix = (int **) malloc(sizeof(*Matrix) * n);
    Matrix = (double **) malloc(sizeof(double*) * n);
    for (i = 0; i < n; i++){
        // Matrix = (int *) malloc(sizeof(*Matrix[i]))
        Matrix[i] = (double *) malloc(sizeof(double));
        if (i < n / 2){
            start = 0; end = m / 2;
        }
        else { start = m / 2; end = m; }
        for (j = 0; j < m; j++){
            Matrix[i][j] = rand()%9 + rand()%99/100. - 5;
            // if ( (i < (m + 1) / 2) && (j < (n + 1) / 2) ) { color_output_green }
            // else if ( (i >= (m + 1) / 2) && (j >= (n + 1) / 2) ) { color_output_green }
            if ( (i < n / 2) && (j < m / 2) ) { color_output_green }
            else if ( (i >= n / 2) && (j >= m / 2) ) { color_output_green }
            else { color_output_white }
            printf("%8.2f", Matrix[i][j]);
        }
        color_output_white
        printf(" | %8.2f", summarize_row(Matrix, i, start, end));
        printf("\n");
    }
    for (int p = 0; p < m; p++){ printf("--------"); } printf("\n");
    for (int column = 0; column < m; column++){ // to be done 
        if (column < m / 2){
            start = 0; end = n / 2;
        }
        else { start = n / 2; end = n; }
        printf("%8.2f", summarize_column(Matrix, column, start, end));
    }
    printf("\n\n");
    
    for (i = 0; i < n; i++){
        free(Matrix[i]); // Returning memory of dinamic strings
        free(Matrix);    // Returning memory of pointers array
    }
}

int main(){
    time_t CT; srand(time(&CT));
    int choise = 0;
    // system("cls");
    while ( (choise != 1) && (choise != 2)) {
        printf("Pick a programm:\n1) Text analyzer\n2) Matrixes\n\n_");
        scanf("%d", &choise);
        system("cls");}

    if (choise == 1) {
        text(100);
    }
    else {
        int n,m;
        printf("enter n, m values:\n");
        scanf("%d", &n); scanf("%d", &m);
        system("cls");
        dinamic_matrixes(n, m);
    }
    system("pause");
    return 0;
}