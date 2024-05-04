#include <iostream>
#include <iomanip>
#include <clocale>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

#define color_output_blue  SetConsoleTextAttribute(hConsole, 3);
#define color_output_green SetConsoleTextAttribute(hConsole, 2);
#define color_output_red   SetConsoleTextAttribute(hConsole, 4);
#define color_output_white SetConsoleTextAttribute(hConsole, 7);


int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Russian");
    // OR
    // setlocale(0, "Russian");
    /*
    // double M[5] = { 0.1, 2.3, 4.5, 6.7, 8.9 };
    // double M[5] = { 0.0, 10.0 };      // 0.0, 10.0, None, None, None
    double M[] = { 0.0, 10.0, -1.2 }; // 0.0, 10.0, -1.2
    for (int i = 0; i < 5; i++) {
        cout << M[1];
    }
    */
    // Array
    /*
    int numbers[] = { 1,2,3,4,5,6,7,8,9,10,11,-12 };
    const int col = 5;
    for (int i = 0; i < 12; i++) {
        cout << numbers[i];

        if ((i + 1) % col) cout << "\t"; // if != 0 !!!
        else cout << "\n";
    }
    // 1       2       3       4       5
    // 6       7       8       9       10
    // 11      - 12
    */
    // Column output
    /*
    const int amount = 100;
    int dig[amount], col;
    for (int i = 0; i < amount; i++) {
        dig[i] = rand(); // [0, 99_999]
        // example:  rand() % 100 => [0, 99]
        // !!! Числа не меняются при перезапуске
        // => Use srand() instead, with changeable argument
        // rand() % 100 / 3.5 => double [0,99.9...]
    }

    cout << "Введите число колонок: \n";
    cin >> col;

    for (int i = 0; i < amount; i++) {
        cout << dig[i];
        if ((i + 1) % col) cout << "\t";
        else cout << "\n";
    }
    */
    // Random numbers
    /*
    time_t current_time;
    srand(time(&current_time));

    const int amount = 100;
    double dig[amount];
    int col;
    for (int i = 0; i < amount; i++) {
        dig[i] = rand() % 1000 / 3.5; // double [0,99.9...]
    }

    cout << "Введите число колонок: \n";
    cin >> col;

    for (int i = 0; i < amount; i++) {
        cout << setw(7) << setprecision(3) << dig[i];
        // setw(n) - n symbols
        // setprecision(m) - m symbols after floating point
        if ((i + 1) % col) cout << "\t";
        else cout << "\n";
    }
    */
    // Outputting an array of completely random doubles 
    // (precision and length)
    /*
    double nm[2][4] = { {11, 12, 13, 14},
                        {21, 22, 23, 24} };
    // double m[][4] = { {1,2,3,4}, {1,0,0,0} } => 2x4 ARRAY
    */
    // Setting up a 2-dimensional array
    /*
    time_t current_time;
    srand(time(&current_time));
    int col;
    cin >> col;

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < col; j++) {
            cout << setw(8) << setprecision(3) << rand() % 100 / 3.5;
        }
        cout << endl;
    }
    */
    // Output
    /*
    time_t current_time;
    srand(time(&current_time));
    const int SIZE = 10;
    int numbers[SIZE];
    int counter = 0;
    for (int i = 0; i < SIZE; i++) { numbers[i] = rand(); }
    for (int i = 0; i < SIZE; i++) { if (numbers[i] != 0) counter++; }
    cout << "Non-zero elements: " << counter << endl;
    */
    // Non-zero elements counter
    /*
    time_t current_time;
    srand(time(&current_time));
    const int SIZE = 10;
    int numbers[SIZE];
    int counter = 0;
    for (int i = 0; i < SIZE; i++) { numbers[i] = rand() % 100; }
   // Simple search without sorting firstly
    bool Found = false;
    int number;
    for (int i = 0; i < SIZE; i++) {
        number = 0;
        while (!Found) {
            if (number == 100) { break; }
            if (numbers[i] == number) { Found = true; }
            else { number++; }
        }
        if (Found = true) {
            cout << number << " is in list\n";
            Found = false;
        }
    }
    */
    // Finding an element
    // ...
    // find max
    // ...
    // sum of columns

    // -------------------------------------------------
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
        if (i % columns == 0) { cout << endl; }
        if (X[i] >= 0) { color_output_blue; }
        else { color_output_red; }
        cout << setw(4) << X[i];
    }
    color_output_white;
    cout << endl << endl;
    cout << "S1 = " << S1 << "\nS2 = " << S2 << endl;

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
            cout << setw(4) << Matrix[i][j];
            avg_sum += Matrix[i][j];
        }
        average[i] = (double) avg_sum / SIZE;
        cout << "   - Average value : " << average[i];
        cout << endl;
    }

    cout << endl << "Sum of Green Area = " << sum << endl;


    system("pause");
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
