#include <iostream>
#include <stdio.h>
#include<conio.h>

#define _CRT_SECURE_NO_WARNINGS
#define ESC 27
#define CR 13

int main()
{
    int i=0;
    char c=' ';
    char ch;

    printf("202007061 백종빈\n");
    printf("command>");

    while (1) {

        ch = _getch();
        printf("%c", ch);
//        printf("\ni 값: %d", i);

        i++;

//        printf("\ni 값: %d", i);

        if (ESC == ch) {
            return 0;
        }

        if (ch == 'q' || ch == 'w' || ch == 'e' || ch == 'r') {
            c = ch;
        }
            
        if (CR == ch && i == 2) {

            switch (c) {
            case 'q':
                printf("\nqqqqqq");
                break;
            case 'w':
                printf("\n과제 너무 wㅗㅎ다");
                break;
            case 'e':
                printf("\n과제 너무 좋ㄷe");
                break;
            case 'r':
                printf("\n과제 너무 좋ㄷr");
                break;
            default:
                printf("\n다시 입력해주세요.");
                break;
            }

            printf("\ncommand>");
//            printf("\ni 값: %d", i);
            i = 0;
            c = ' ';
        }
        else if (CR == ch) {
            printf("\n다시 입력해주세요.");
            printf("\ncommand>");
//            printf("\ni 값: %d", i);
            i = 0;
            c = ' ';
        }

    }

}

