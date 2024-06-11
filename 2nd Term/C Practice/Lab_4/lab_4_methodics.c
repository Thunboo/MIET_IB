#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define color_output_blue  SetConsoleTextAttribute(hConsole, 3);
#define color_output_green SetConsoleTextAttribute(hConsole, 2);
#define color_output_red   SetConsoleTextAttribute(hConsole, 4);
#define color_output_white SetConsoleTextAttribute(hConsole, 7);


void input( int *p){
    printf("\nInput X value:");
    scanf("%d", p);
}
int input_in_work(){
    int x = 0;
    input(&x);
    printf("X = %d", x);
    return 0;
}

int rnd_array(){
    
    time_t current_time;
    srand(time(&current_time));

    int N = 20, i = 0, COLUMNS = 5;
    double *ptr, numbers[N], sum;

    for (ptr = numbers; ptr < &numbers[0] + N; ptr++){
        *ptr = rand() % 99 + (double) rand() / 100;
        }
    /*
    for (ptr = numbers, i = 0; ptr < numbers; ptr++, i++){
        printf("YES\n");
        printf("%8.2f", *ptr);
        //if ( (i + 1) % COLUMNS) printf("\t");
        //else printf("\n");
    } */
    ptr = numbers; while(1){
        if ( i == N) { break; }
        printf("%8.2f ", *ptr);
        if (!( (i + 1) % COLUMNS)) { printf("\n"); }
        ptr++; i++;
    }
    for (sum = 0, ptr = &numbers[0]; ptr < numbers + N; ptr++){
        sum += *ptr;
    }
    printf("Sum = %.1f \n", sum);

    system("PAUSE");
    return 0;
}

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
            *result = *ptr_local; // FOR OUTPUTING AN ARRAY
            result++;
        }
    }
    return (result - output_array); // length of array of negative elements
}

int main(){
    time_t current_time;
    srand(time(&current_time));
    int N = 20, COL = 5;
    double array[N]; // ВНЕШНЯЯ ПАМЯТЬ
    double rez[N];

    initialize_array(array, N);
    double *minimal = minimum(array, N);
    print_array(array, N, COL);
    printf(" Sum = %.2f \n", summarize_array(array, N));
    printf(" Minimum = %.2f \n", *minimal);
    if (minimal == array) {
        printf(" Next element : %.2f", *(minimal + 1)); }
    else if (minimal == array + N - 1){
        printf(" Previous element : %.2f", *(minimal - 1)); }
    else {
        printf(" Surround = %.2f | %.2f\n", *(minimal - 1), *(minimal + 1)); 
        }
    printf("There is %d negative elements\n", negative_elements_counter(array, N, rez));
    for (int i = 0; i < N; i++){ printf("%8.2f", rez[i]); }

    system("PAUSE");
    return 0;
}


int not_main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    time_t current_time;
    srand(time(&current_time));


    int x, *pX;
    pX = &x;  // set pX equal to x's address
    // * - РАЗЫМЕНОВАНИЕ !!!
    x = 1;
    *pX = *pX + 7;
    printf("*pX = %d | x = %d \n\n", *pX, x);

    char A[100], i, *pA;
    A[0] = 'a', A[1] = 'b', A[2] = 'c';
    pA = A; // or pA = &A[0];
    // A[0]   <=> *(pointer_to_A + 0)   <=> pointer_to_A[0]
    // A[10]  <=> *(pointer_to_A + 10)  <=> pointer_to_A[10]
    // A[n-1] <=> *(pointer_to_A + n-1) <=> pointer_to_A[n-1]
    printf("A[0-2] : %c %c %c \n\
*(pA + 0-2) : %c %c %c \n\
pA[0-2] : %c %c %c \n", 
A[0], A[1], A[2], *(pA + 0), *(pA + 1), *(pA + 2), pA[0], pA[1], pA[2]);


    int N = 5, AI[N], *p_AI;
    for (int i = 1; i < 6; i++){
        AI[i - 1] = i;
        }
    p_AI = &AI[0]; // OR p_AI = AI
    for (int i = 0; i < 5; i++){
        printf("&AI[%d] = %d | AI[%d] = %d\n", i, &AI[i], i, AI[i]);
    }
    printf("\np_AI = &AI[0] = %d | *p_AI = %d\np_AI = &AI[N-1] = %d | *(p_AI + N - 1) = %d \np_AI = p_AI + 3 = %d",
                     &AI[0],       *p_AI,             &AI[N-1],       *(p_AI + N - 1),              p_AI + 3);
    
    printf("\n----------------\n");

    for (p_AI = &AI[0]; p_AI <= &AI[N - 1]; p_AI += 2){
        printf("*p_AI = %d\n", *p_AI);
    }
    // PRINTING ODD ELEMENTS VIA POINTER
    for (p_AI = &AI[N - 1]; p_AI >= &AI[0]; p_AI -= 1){
        printf("*p_AI = %d | %d\n", *p_AI, p_AI);
    }
    // PRINTING ELEMENTS IN REVERSED ORDER VIA POINTER


    return 0;
}