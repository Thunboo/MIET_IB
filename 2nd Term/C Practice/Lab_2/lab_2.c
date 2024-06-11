//#include <iostream>
//#include <iomanip>
//#include <clocale>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

//using namespace std;

#define color_output_blue  SetConsoleTextAttribute(hConsole, 3);
#define color_output_green SetConsoleTextAttribute(hConsole, 2);
#define color_output_red   SetConsoleTextAttribute(hConsole, 4);
#define color_output_white SetConsoleTextAttribute(hConsole, 7);


int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //setlocale(LC_ALL, "Russian");

    // The begining of the first program
    time_t current_time;
    srand(time(&current_time));

    const int N = 20;
    const int columns = 5;
    int X[N];
    int S1 = 0, S2 = 0;

    for (int i = 0; i < N; i++) {
        X[i] = rand() % 100;
        if (rand() % 2 == 0) { X[i] *= -1; }
    }

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


    system("pause");
    return 0;
}
