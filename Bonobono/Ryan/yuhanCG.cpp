#include "yuhanCG.h"

void DrawBonobono(HWND hWnd, HDC hdc, int blink) {
    // 피부 그리기
    HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255));
    HBRUSH eyeBrush = CreateSolidBrush(RGB(0, 0, 0)); // 눈 색상 (검정)
    HBRUSH ineyeBrush = CreateSolidBrush(RGB(255, 255, 255)); // 눈동자 색상 (하양)
    SelectObject(hdc, hBrush);
    Ellipse(hdc, 200, 100, 580, 450);

    // 입 그리기 
    HBRUSH mouseBrush = CreateSolidBrush(RGB(255, 150, 255)); // 입 색상 (핑크)
    SelectObject(hdc, mouseBrush);
    Chord(hdc, 365, 260, 405, 350, 0, 0, 0, 0);

    //하얀볼 그리기
    HBRUSH ballBrush = CreateSolidBrush(RGB(255, 255, 255)); // 눈 색상 (하양)
    SelectObject(hdc, ballBrush);
    Ellipse(hdc, 325, 275, 385, 320); // 왼쪽 볼
    Ellipse(hdc, 390, 275, 450, 320); // 오른쪽 볼

    // 코 그리기 (작은 동그라미)
    HBRUSH noseBrush = CreateSolidBrush(RGB(0, 0, 0)); // 코 색상 (검정)
    SelectObject(hdc, noseBrush);
    Ellipse(hdc, 365, 260, 405, 300); // 코


    if (blink) {
        // ㅡ ㅡ 그리기
        HPEN eyePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
        SelectObject(hdc, eyePen);
        MoveToEx(hdc, 230, 230, NULL);
        LineTo(hdc, 250, 230);
        MoveToEx(hdc, 530, 230, NULL);
        LineTo(hdc, 550, 230);
        DeleteObject(eyePen);
    }
    else {
        // 눈 그리기
        SelectObject(hdc, eyeBrush);
        Ellipse(hdc, 230, 220, 250, 240); // 왼쪽 눈
        Ellipse(hdc, 530, 220, 550, 240); // 오른쪽 눈

        // 눈동자 그리기
        SelectObject(hdc, ineyeBrush);
        Ellipse(hdc, 232, 222, 248, 238); // 왼쪽 눈동자
        Ellipse(hdc, 532, 222, 548, 238); // 오른쪽 
    }

    // 수염 그리기 (선)
    HPEN beardPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // 수염 색상 (검정)
    SelectObject(hdc, beardPen);
    MoveToEx(hdc, 350, 290, NULL);
    LineTo(hdc, 300, 265);
    MoveToEx(hdc, 430, 290, NULL);
    LineTo(hdc, 470, 265);

    MoveToEx(hdc, 350, 305, NULL);
    LineTo(hdc, 300, 305);
    MoveToEx(hdc, 430, 305, NULL);
    LineTo(hdc, 470, 305);

    // 리소스 해제
    DeleteObject(hBrush);
    DeleteObject(eyeBrush);
    DeleteObject(ballBrush);
    DeleteObject(noseBrush);
    DeleteObject(ineyeBrush);
    DeleteObject(mouseBrush);
    DeleteObject(beardPen);
}

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
    int faceWidth = right - left;
    int faceHeight = bottom - top;

    // 메인 얼굴의 중심 계산
    int centerX = (left + right) / 2;
    int centerY = (top + bottom) / 2;

    // 귀의 크기 계산
    int earWidth = faceWidth * 0.4; // 예시로 20%로 설정, 조절 가능
    int earHeight = faceHeight * 0.5; // 예시로 30%로 설정, 조절 가능

    // 얼굴 중심으로부터의 거리 계산
    int distanceFromCenter = faceWidth * 0.3; // 예시로 30%로 설정, 조절 가능

    // 왼쪽 귀 중심 계산
    int leftEarCenterX = centerX - distanceFromCenter;
    int leftEarCenterY = centerY - faceHeight * 0.4; // 얼굴 높이의 40%만큼 위에 위치

    // 오른쪽 귀 중심 계산
    int rightEarCenterX = centerX + distanceFromCenter;
    int rightEarCenterY = centerY - faceHeight * 0.4; // 얼굴 높이의 40%만큼 위에 위치

    // 귀 그리기
    HBRUSH earBrush = CreateSolidBrush(RGB(255, 200, 15)); // 귀 색상
    SelectObject(hdc, earBrush);

    // 왼쪽 귀
    Chord(hdc, leftEarCenterX - earWidth / 2, leftEarCenterY - earHeight / 2, leftEarCenterX + earWidth / 2, leftEarCenterY + earHeight / 2, 0, 0, 0, 0);

    // 오른쪽 귀
    Chord(hdc, rightEarCenterX - earWidth / 2, rightEarCenterY - earHeight / 2, rightEarCenterX + earWidth / 2, rightEarCenterY + earHeight / 2, 0, 0, 0, 0);


    // 얼굴 그리기
    HBRUSH faceBrush = CreateSolidBrush(RGB(255, 200, 15)); // 얼굴 색상
    SelectObject(hdc, faceBrush);
    Chord(hdc, left, top, right, bottom, 0, 0, 0, 0);


    // 눈썹 그리기
    HPEN browPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // 눈썹 색상
    SelectObject(hdc, browPen);

    // 왼쪽 눈썹
    MoveToEx(hdc, leftEarCenterX - earWidth / 18 - 20, leftEarCenterY + earHeight / 2 - 1, NULL);
    LineTo(hdc, leftEarCenterX - earWidth / 18 + 20, leftEarCenterY + earHeight / 2 - 1);

    MoveToEx(hdc, leftEarCenterX - earWidth / 18 - 20, leftEarCenterY + earHeight / 2, NULL);
    LineTo(hdc, leftEarCenterX - earWidth / 18 + 20, leftEarCenterY + earHeight / 2);

    MoveToEx(hdc, leftEarCenterX - earWidth / 18 - 20, leftEarCenterY + earHeight / 2 + 1, NULL);
    LineTo(hdc, leftEarCenterX - earWidth / 18 + 20, leftEarCenterY + earHeight / 2 + 1);

    // 오른쪽 눈썹
    MoveToEx(hdc, rightEarCenterX + earWidth / 18 - 20, rightEarCenterY + earHeight / 2 - 1, NULL);
    LineTo(hdc, rightEarCenterX + earWidth / 18 + 20, rightEarCenterY + earHeight / 2 - 1);

    MoveToEx(hdc, rightEarCenterX + earWidth / 18 - 20, rightEarCenterY + earHeight / 2, NULL);
    LineTo(hdc, rightEarCenterX + earWidth / 18 + 20, rightEarCenterY + earHeight / 2);

    MoveToEx(hdc, rightEarCenterX + earWidth / 18 - 20, rightEarCenterY + earHeight / 2 + 1, NULL);
    LineTo(hdc, rightEarCenterX + earWidth / 18 + 20, rightEarCenterY + earHeight / 2 + 1);


    // 눈 그리기
    HBRUSH eyeBrush = CreateSolidBrush(RGB(0, 0, 0)); // 눈 색상
    SelectObject(hdc, eyeBrush);

    //왼쪽 눈
    Ellipse(hdc, leftEarCenterX - earWidth / 25 - 10, leftEarCenterY + earHeight / 1.8 + 5,
        leftEarCenterX - earWidth / 25 + 10, leftEarCenterY + earHeight / 1.8 + 20);

    //오른쪽 눈
    Ellipse(hdc, rightEarCenterX + earWidth / 25 - 10, rightEarCenterY + earHeight / 1.8 + 5,
        rightEarCenterX + earWidth / 25 + 10, rightEarCenterY + earHeight / 1.8 + 20);

    // 코 그리기
    HBRUSH noseBrush = CreateSolidBrush(RGB(0, 0, 0));  // 코 색상
    SelectObject(hdc, noseBrush);

    int noseRadius = 7;  // Adjust the radius of the nose as needed

    Chord(hdc, centerX - noseRadius, centerY - noseRadius, centerX + noseRadius, centerY + noseRadius, 0, 0, 0, 0);

    // 볼 포인트 그리기
    HBRUSH cheekBrush = CreateSolidBrush(RGB(255, 255, 255)); // 볼 포인트 색상
    SelectObject(hdc, cheekBrush);

    int cheekRadius = 20;  // Adjust the radius of the cheeks as needed

    // 왼쪽 볼
    Chord(hdc, centerX - noseRadius - cheekRadius - 7, centerY + noseRadius - 7, centerX - noseRadius + 7, centerY + noseRadius + cheekRadius + 7, 0, 0, 0, 0);

    // 오른쪽 볼
    Chord(hdc, centerX + noseRadius - 7, centerY + noseRadius - 7, centerX + noseRadius + cheekRadius + 7, centerY + noseRadius + cheekRadius + 7, 0, 0, 0, 0);

    //// 리소스 해제
    DeleteObject(earBrush);
    DeleteObject(faceBrush);
    DeleteObject(browPen);
    DeleteObject(eyeBrush);
    DeleteObject(noseBrush);
    DeleteObject(cheekBrush);
}