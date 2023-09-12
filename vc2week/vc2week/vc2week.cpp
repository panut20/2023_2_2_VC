#include <iostream>
#include <stdio.h>
#include<conio.h>

#define _CRT_SECURE_NO_WARNINGS
#define ESC 27

int main()
{
    char a;
    char ch;

    printf("202007061 백종빈\n");
    
    while (1) {

        ch = _getch();
        if (ESC == ch)
            return 0;

        printf("command>");
        scanf_s(" %c", &a, 1);

        switch (a) {
        case 'q':
            printf("qqqqqq\n");
            break;
        case 'w':
            printf("과제 너무 wㅗㅎ다\n");
            break;
        case 'e':
            printf("과제 너무 좋ㄷe\n");
            break;
        case 'r':
            printf("과제 너무 좋ㄷr\n");
            break;
        default:
            break;
        }


    }

    
}

