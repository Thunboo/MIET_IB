#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main(){
    //printf("Hello world! \n");

    const int a = 5;
    long int b = 15;
    unsigned int c = 25;
    // int a,b,c;
    // a = 1
    // b = 2 ...

    /*
    Ключевые слова:
    int, long, short, float, double, char, bool

    Модификаторы:
    signed, unsigned

    long long ???
    */
    //printf("%d:%d:%i", a,b,c);
    //printf("\n");
    
    double pi = 3.14;
    char ch = 'c';
    int one = 1;
    long l;
    double sum;

    sum = pi*(double)(one + ch/l);
    /*
        ch -> long и one -> long
        => type(one + ch/l) = long
        -> double
    */
    //printf("%f", sum);

    /*
        >
        <
        >=
        <=
        ==
        !=
-----------------
        && - И
        || - ИЛИ
        !  - НЕ
    */
/*  if (2 > 1){
        printf("2 is more than 1");
    }
    else{printf("WHAT?!?");}
*/
    
    int x;
    printf("Input a value between 1 and 3:");
    scanf("%d, &x");
    switch(x){
        case 1: 
            printf("x = 1"); break;
        case 2: 
        case 3: 
            printf("x = 2 or 3"); break;
        default: 
            printf("x is not in [1,2,3]"); break;
    }
    system("pause");
    return 0;
}