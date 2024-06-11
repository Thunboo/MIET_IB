#include <windows.h>
#include <locale.h>

#define RED             "\x1b[31m"
#define GREEN           "\x1b[32m"
#define YELLOW          "\x1b[33m"
#define BLUE            "\x1b[34m"
#define MAGENTA         "\x1b[35m"
#define CYAN            "\x1b[36m"
#define RESET_COLOR     "\x1b[0m"

//#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
//#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

void enable_colors() {
    HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode( handleOut , &consoleMode);
    consoleMode |= 0x0004;           
    SetConsoleMode( handleOut , consoleMode );
}

void Rus_text(){
    setlocale(LC_ALL, "Rus");
}

void set_utf_8() {
    if (SetConsoleCP(65001) == 0)
        printf(RED "utf-8 SetConsoleCP failure\n" RESET_COLOR);
    if (SetConsoleOutputCP(65001) == 0)
        printf(RED "utf-8 SetConsoleOutputCP failure\n" RESET_COLOR);
}