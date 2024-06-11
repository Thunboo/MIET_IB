#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define color_output_blue  SetConsoleTextAttribute(hConsole, 3);
#define color_output_green SetConsoleTextAttribute(hConsole, 2);
#define color_output_red   SetConsoleTextAttribute(hConsole, 4);
#define color_output_white SetConsoleTextAttribute(hConsole, 7);

int MIN(a, b){
    return ((a) < (b) ? (a) : (b));
    //if (a < b){ return a;} return b;
}
int MAX(a, b){
    return ((a) > (b) ? (a) : (b));
}

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    time_t current_time;
    srand(time(&current_time));

    const int N1 = 22, N2 = 20;
    const int columns = 11;
    int A[N1], B[N2];
    int last_pos_elem_id_1, last_pos_elem_id_2, min_1, min_2;

    for (int i = 0; i < N1; i++) {
        A[i] = rand() % 100;
        if (rand() % 2 == 0) { A[i] *= -1; }
    }
    for (int i = 0; i < N2; i++) {
        B[i] = rand() % 100;
        if (rand() % 2 == 0) { B[i] *= -1; }
    }
///////////////////////
    min_1 = A[0];
    for (int i = 1; i < N1; i++){
        min_1 = MAX(min_1, A[i]);
    } 

    for (int i = N1 - 1; i > -1; i--){
        if (A[i] > 0){
            last_pos_elem_id_1 = i;
            break;
            }
    }

    for (int i = 0; i < last_pos_elem_id_1; i++){
        min_1 = MIN(min_1, A[i]);
    }
    // [ 0 -1 2 3 -4 -5 -6 7 -8 -9 ||| 10 ] //
///////////////////////
    min_2 = B[0];
    for (int i = 1; i < N2; i++){
        min_2 = MAX(min_2, B[i]);
    }

    for (int i = N2 - 1; i > -1; i--){
        if (B[i] > 0){
            last_pos_elem_id_2 = i;
            break;
            }
    }

    for (int i = 0; i < last_pos_elem_id_2; i++){
        min_2 = MIN(min_2, B[i]);
    }
///////////////////////
for (int i = 0; i < N1; i++) {
        if (i % columns == 0) { printf("\n"); }
        if (i < last_pos_elem_id_1) { color_output_blue; }
        else { color_output_red; }
        printf("%4d", A[i]);
    }
    color_output_green;
    printf("\n\nMinimal element = %d\n\n", min_1);
    system("pause");
    system("cls");

for (int i = 0; i < N2; i++) {
        if (i % columns == 0) { printf("\n"); }
        if (i < last_pos_elem_id_2) { color_output_blue; }
        else { color_output_red; }
        printf("%4d", B[i]);
    }
    color_output_green;
    printf("\n\nMinimal element = %d\n\n", min_2);
/*
    for (int i = 0; i < N / 2; i++) {
        if (X[i] > 0) {
            S1 += X[i];
        }
    }
    for (int i = N / 2; i < N; i++) {
        if (X[i] < 0) {
            S2 += X[i];
        }
    }

    for (int i = 0; i < N; i++) {
        if (i % columns == 0) { printf("\n"); }
        if (X[i] >= 0) { color_output_blue; }
        else { color_output_red; }
        printf("%4d", X[i]);
    }
    color_output_white;
    printf("\n\n");
    printf("S1 = %d\nS2 = %d\n\n", S1, S2);

    // The ending of the first program
    system("pause");
    system("cls");
    // ----------------------------------------------------
    // The begining of the second program

    const int SIZE = 8;
    int Matrix[SIZE][SIZE];
    int sum = 0, avg_sum = 0;
    double average[SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            Matrix[i][j] = rand() % 100;
            if (rand() % 2 == 0) { Matrix[i][j] *= -1; }
            }
        }

    for (int i = 0; i < SIZE; i++) {
        avg_sum = 0;
        color_output_green;
        for (int j = 0; j < SIZE; j++) {
            if (i + j > SIZE - 1) { color_output_white; }
            else { sum += Matrix[i][j]; }
            printf("%4.d", Matrix[i][j]);
            avg_sum += Matrix[i][j];
        }
        average[i] = (double) avg_sum / SIZE;
        printf("   - Average value : %lf \n", average[i]);
    }

    printf("\n\nSum of Green Area = %d\n\n", sum);

*/
    system("pause");
    return 0;
}
