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
}
int MAX(a, b){
    return ((a) > (b) ? (a) : (b));
}

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    time_t current_time;
    srand(time(&current_time));

    const int N = 10, M = 12;
    int X[N*M];
    int minimal_value = 1000;

    for (int i = 0; i < N*M; i++) {
        X[i] = rand() % 100;
        if (rand() % 2 == 0) { X[i] *= -1; }
    }

    for (int i = 0; i < N*M; i++) {
        if (i % N == 0) { 
            if (i > N*M/2) { 
                color_output_green;
                printf("   - min positive = %d", minimal_value);
                minimal_value = 1000; 
            } 
            printf("\n"); }
        if (X[i] > 0) {
            color_output_blue; 
            minimal_value = MIN(minimal_value, X[i]);
        }
        else { color_output_red; }
        printf("%4d", X[i]);
    }

    color_output_green;
    printf("   - min positive = %d", minimal_value);
    printf("\n\n\n");
    system("pause");
    // ----------------------------------------------------
    return 0;
}
