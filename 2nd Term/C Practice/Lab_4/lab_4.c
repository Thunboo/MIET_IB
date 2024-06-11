#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define color_output_blue  SetConsoleTextAttribute(hConsole, 3);
#define color_output_green SetConsoleTextAttribute(hConsole, 2);
#define color_output_red   SetConsoleTextAttribute(hConsole, 4);
#define color_output_white SetConsoleTextAttribute(hConsole, 7);

void initialize_array(double *array, int n){
    double *ptr_local;
    for (ptr_local = array; ptr_local < (array + n); ptr_local++){
        *ptr_local = rand()%99 + rand()%99/100. - 50;
    }
}
void print_array(double *array, int len_array, int column_width){
    for (int i = 0; i < len_array; i++, array++){
        printf("%8.2f", *array);
        if (!( (i + 1) % column_width )){ printf("\n"); }
    }
    printf("\n");
}
double summarize_array(double *array, int len_array){
    double sum_of_array, *ptr_local;
    for (ptr_local = array, sum_of_array = 0; ptr_local < array + len_array; ptr_local++ ){
        sum_of_array += *ptr_local;
    }
    return sum_of_array;
}
double *minimum(double *array, int len_array){
    double *ptr_local, *ptr_min;
    for (ptr_local = ptr_min = array; ptr_local < array + len_array; ptr_local++){
        if ( *ptr_min > *ptr_local) { ptr_min = ptr_local; }
    }
    return ptr_min;
}
int negative_elements_counter(double *array, int len_array, double *output_array){
    double *ptr_local, *result;
    for (ptr_local = array, result = output_array; ptr_local < (array + len_array); ptr_local++){
        if (*ptr_local < 0){
            //*result = *ptr_local; // FOR OUTPUTING AN ARRAY
            result++;
        }
    }
    return (result - output_array); // length of array of negative elements
}

double *min_max_custom(double *array, int N){ //}, double *min, double *max){
    double *ptr_local, *ptr_min, *ptr_max;
    ptr_local = ptr_min = ptr_max = array; 
    for (int i = 0; i < N; i++){        // СТРОКА
        for (int j = 0; j < N; j++){    // ЭЛЕМЕНТ № j
            if ( i + j < N){
                ptr_local = array + i * N + j;
                printf("%8.2f", *ptr_local);
                if ( *ptr_min > *ptr_local) { ptr_min = ptr_local; }
                if ( *ptr_max < *ptr_local) { ptr_max = ptr_local; }
            }
        }
        printf("\n");
    }
    //min = ptr_min; max = ptr_max;
    double m_m[2] = {*ptr_min, *ptr_max};
    return m_m;
}
double *min_custom(double *array, int N){
    double *ptr_local, *ptr_min;
    ptr_local = ptr_min = array;
    for (int i = 0; i < N; i++){        // СТРОКА
        for (int j = 0; j < N; j++){    // ЭЛЕМЕНТ № j
            if ( i + j < N){
                ptr_local = array + i * N + j;
                printf("%8.2f", *ptr_local);
                if ( *ptr_min > *ptr_local) { ptr_min = ptr_local; }
            }
        }
        printf("\n");
    }
    return ptr_min;
}
double *max_custom(double *array, int N){
    double *ptr_local, *ptr_max;
    ptr_local = ptr_max = array;
    for (int i = 0; i < N; i++){        // СТРОКА
        for (int j = 0; j < N; j++){    // ЭЛЕМЕНТ № j
            if ( i + j < N){
                ptr_local = array + i * N + j;
                if ( *ptr_max < *ptr_local) { ptr_max = ptr_local; }
            }
        }
    }
    return ptr_max;
}

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    time_t current_time;
    srand(time(&current_time));
    int N1 = 20, N2 = 25, COL = 5;
    double A[N1], B[N2];

    initialize_array(A, N1);
    double *minimal_A = minimum(A, N1);
    double summ_A = summarize_array(A, (minimal_A - A));
    print_array(A, N1, COL);

    printf("Minimum : %.2f\nMinimum ID : %d | It's the %d-th element\n", *minimal_A, (minimal_A - A), (minimal_A - A) + 1);
    printf("Sum of 1st part of array A = %.2f\n", summ_A);
    
    printf("--------------------------------\n");

    initialize_array(B, N2);
    double *minimal_B = minimum(B, N2);
    double summ_B = summarize_array(B, (minimal_B - B));
    print_array(B, N2, COL);

    printf("Minimum : %.2f\nMinimum ID : %d | It's the %d-th element\n", *minimal_B, (minimal_B - B), (minimal_B - B) + 1);
    printf("Sum of 1st part of array B = %.2f\n", summ_B);

    printf("--------------------------------\n");

    if (summ_A > summ_B) printf("Sum A > Sum B\n");
    else printf("Sum B > Sum A\n");

    printf("--------------------------------\n");
    printf("CONTINUE ? (press any button)");
    system("PAUSE");
    system("CLS");
    

    int N = 6;
    double Matrix[N*N];
    initialize_array(Matrix, N*N);

    color_output_blue
    double *minimal = min_custom(Matrix, N), *maximal = max_custom(Matrix, N);
    color_output_white
    
    print_array(Matrix, N*N, N);

    printf("MIN : %.2f\nMAX : %.2f\n", *minimal, *maximal);
    //color_output_blue
    //double *minimal, *maximal;
    //minimal = Matrix; maximal = NULL;
    //min_max_custom(Matrix, N, minimal, maximal);
    //color_output_white
    //printf("MIN : %.2f\nMAX : %.2f\n", *minimal, *maximal);

    system("PAUSE");
    return 0;

}