#include <iostream>
#include<stdio.h>
#include<conio.h>
#include <chrono>  // 시간작업관련 c 런타임 time보다 정확.

#define ESC 27
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

void arrow(char ch); // 화살표로 시작하는 커맨드 모은 함수
void ehqkf(char ch); // 도발 커맨드 함수
void flying(char ch); // 어퍼컷 커맨드 함수

int main()
{

    char ch = ' ';

    printf("↑+ a + s = 아따따뚜겐~\n");
    printf("a + ↑ + a = 어퍼컷\n");
    printf("→+→ = 앞대쉬\n");
    printf("←+← = 백대쉬\n");
    printf("도발\n");

    while (ch != ESC) {

        ch = _getch();

        if (ch == -32) {
            arrow(ch);
        }

        if (ch == 'e') {
            ehqkf(ch);
        }

        if (ch == 'a') {
            flying(ch);
        }
    }
}


    void arrow(char ch) {

        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

        if (ch == -32) {
            ch = _getch();
            if (ch == UP) {
                ch = _getch();
                if (ch == 'a') {
                    ch = _getch();
                    std::chrono::duration<double>sec = std::chrono::system_clock::now() - start; // 완성 직전에 시간체크 및 0.3초 체크
                    if (ch == 's' && sec.count() <= 0.3) {
                        printf("아따따뚜겐~\n");
                    }
                }
            }

            if (ch == LEFT) {
                ch = _getch();
                ch = _getch();
                std::chrono::duration<double>sec = std::chrono::system_clock::now() - start;
                if (ch == LEFT && sec.count() <= 0.3) {
                    printf("백대쉬\n");
                }
            }

            if (ch == RIGHT) {
                ch = _getch();
                ch = _getch();
                std::chrono::duration<double>sec = std::chrono::system_clock::now() - start;
                if (ch == RIGHT && sec.count() <= 0.3) {
                    printf("앞대쉬\n");
                }
            }
        }
    }

    void ehqkf(char ch) {

        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

        if (ch == 'e') {
            ch = _getch();
            if (ch == 'h') {
                ch = _getch();
                if (ch == 'q') {
                    ch = _getch();
                    if (ch == 'k') {
                        ch = _getch();
                        std::chrono::duration<double>sec = std::chrono::system_clock::now() - start;
                        if (ch == 'f' && sec.count() <= 0.3) {
                            printf("그렇게 하는거 아닌데~~ ~.~\n");
                        }
                    }
                }
            }
        }
    }

    void flying(char ch) {

        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

        if (ch == 'a') {
            ch = _getch();
            if (ch == -32) {
                ch = _getch();
                if (ch == UP) {
                    ch = _getch();
                    std::chrono::duration<double>sec = std::chrono::system_clock::now() - start;
                    if (ch == 'a' && sec.count() <= 0.3) {
                        printf("어퍼컷\n");
                    }
                }
            }
        }
    }