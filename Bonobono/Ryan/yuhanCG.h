#pragma once
#include<Windows.h>

void DrawBonobono(HWND hWnd, HDC hdc, int blink);
void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);
void DrawRect(HWND hWnd, HDC hdc, RECT rect);
void DrawingArea(HWND hWnd, HDC hdc, RECT drawRect, RECT borderRect, const wchar_t* text);
void DrawCircle(HWND hWnd, HDC hdc, int circle_left, int circle_top, int circle_right, int circle_bottom);