#pragma once
#include<Windows.h>

void DrawBonobono(HWND hWnd, HDC hdc, int blink);
void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);
void drawrect(HWND hWnd, HDC hdc, RECT rect);
void drawingarea(HWND hWnd, HDC hdc, RECT drawRect, RECT borderRect, const wchar_t* text);