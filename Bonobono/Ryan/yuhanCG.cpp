#include "yuhanCG.h"

void DrawBonobono(HWND hWnd, HDC hdc, int blink) {
    // �Ǻ� �׸���
    HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255));
    HBRUSH eyeBrush = CreateSolidBrush(RGB(0, 0, 0)); // �� ���� (����)
    HBRUSH ineyeBrush = CreateSolidBrush(RGB(255, 255, 255)); // ������ ���� (�Ͼ�)
    SelectObject(hdc, hBrush);
    Ellipse(hdc, 200, 100, 580, 450);

    // �� �׸��� 
    HBRUSH mouseBrush = CreateSolidBrush(RGB(255, 150, 255)); // �� ���� (��ũ)
    SelectObject(hdc, mouseBrush);
    Chord(hdc, 365, 260, 405, 350, 0, 0, 0, 0);

    //�ϾẼ �׸���
    HBRUSH ballBrush = CreateSolidBrush(RGB(255, 255, 255)); // �� ���� (�Ͼ�)
    SelectObject(hdc, ballBrush);
    Ellipse(hdc, 325, 275, 385, 320); // ���� ��
    Ellipse(hdc, 390, 275, 450, 320); // ������ ��

    // �� �׸��� (���� ���׶��)
    HBRUSH noseBrush = CreateSolidBrush(RGB(0, 0, 0)); // �� ���� (����)
    SelectObject(hdc, noseBrush);
    Ellipse(hdc, 365, 260, 405, 300); // ��


    if (blink) {
        // �� �� �׸���
        HPEN eyePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
        SelectObject(hdc, eyePen);
        MoveToEx(hdc, 230, 230, NULL);
        LineTo(hdc, 250, 230);
        MoveToEx(hdc, 530, 230, NULL);
        LineTo(hdc, 550, 230);
        DeleteObject(eyePen);
    }
    else {
        // �� �׸���
        SelectObject(hdc, eyeBrush);
        Ellipse(hdc, 230, 220, 250, 240); // ���� ��
        Ellipse(hdc, 530, 220, 550, 240); // ������ ��

        // ������ �׸���
        SelectObject(hdc, ineyeBrush);
        Ellipse(hdc, 232, 222, 248, 238); // ���� ������
        Ellipse(hdc, 532, 222, 548, 238); // ������ 
    }

    // ���� �׸��� (��)
    HPEN beardPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // ���� ���� (����)
    SelectObject(hdc, beardPen);
    MoveToEx(hdc, 350, 290, NULL);
    LineTo(hdc, 300, 265);
    MoveToEx(hdc, 430, 290, NULL);
    LineTo(hdc, 470, 265);

    MoveToEx(hdc, 350, 305, NULL);
    LineTo(hdc, 300, 305);
    MoveToEx(hdc, 430, 305, NULL);
    LineTo(hdc, 470, 305);

    // ���ҽ� ����
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

    // ���� ���� �߽� ���
    int centerX = (left + right) / 2;
    int centerY = (top + bottom) / 2;

    // ���� ũ�� ���
    int earWidth = faceWidth * 0.4; // ���÷� 20%�� ����, ���� ����
    int earHeight = faceHeight * 0.5; // ���÷� 30%�� ����, ���� ����

    // �� �߽����κ����� �Ÿ� ���
    int distanceFromCenter = faceWidth * 0.3; // ���÷� 30%�� ����, ���� ����

    // ���� �� �߽� ���
    int leftEarCenterX = centerX - distanceFromCenter;
    int leftEarCenterY = centerY - faceHeight * 0.4; // �� ������ 40%��ŭ ���� ��ġ

    // ������ �� �߽� ���
    int rightEarCenterX = centerX + distanceFromCenter;
    int rightEarCenterY = centerY - faceHeight * 0.4; // �� ������ 40%��ŭ ���� ��ġ

    // �� �׸���
    HBRUSH earBrush = CreateSolidBrush(RGB(255, 200, 15)); // �� ����
    SelectObject(hdc, earBrush);

    // ���� ��
    Chord(hdc, leftEarCenterX - earWidth / 2, leftEarCenterY - earHeight / 2, leftEarCenterX + earWidth / 2, leftEarCenterY + earHeight / 2, 0, 0, 0, 0);

    // ������ ��
    Chord(hdc, rightEarCenterX - earWidth / 2, rightEarCenterY - earHeight / 2, rightEarCenterX + earWidth / 2, rightEarCenterY + earHeight / 2, 0, 0, 0, 0);


    // �� �׸���
    HBRUSH faceBrush = CreateSolidBrush(RGB(255, 200, 15)); // �� ����
    SelectObject(hdc, faceBrush);
    Chord(hdc, left, top, right, bottom, 0, 0, 0, 0);


    // ���� �׸���
    HPEN browPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // ���� ����
    SelectObject(hdc, browPen);

    // ���� ����
    MoveToEx(hdc, leftEarCenterX - earWidth / 18 - 20, leftEarCenterY + earHeight / 2 - 1, NULL);
    LineTo(hdc, leftEarCenterX - earWidth / 18 + 20, leftEarCenterY + earHeight / 2 - 1);

    MoveToEx(hdc, leftEarCenterX - earWidth / 18 - 20, leftEarCenterY + earHeight / 2, NULL);
    LineTo(hdc, leftEarCenterX - earWidth / 18 + 20, leftEarCenterY + earHeight / 2);

    MoveToEx(hdc, leftEarCenterX - earWidth / 18 - 20, leftEarCenterY + earHeight / 2 + 1, NULL);
    LineTo(hdc, leftEarCenterX - earWidth / 18 + 20, leftEarCenterY + earHeight / 2 + 1);

    // ������ ����
    MoveToEx(hdc, rightEarCenterX + earWidth / 18 - 20, rightEarCenterY + earHeight / 2 - 1, NULL);
    LineTo(hdc, rightEarCenterX + earWidth / 18 + 20, rightEarCenterY + earHeight / 2 - 1);

    MoveToEx(hdc, rightEarCenterX + earWidth / 18 - 20, rightEarCenterY + earHeight / 2, NULL);
    LineTo(hdc, rightEarCenterX + earWidth / 18 + 20, rightEarCenterY + earHeight / 2);

    MoveToEx(hdc, rightEarCenterX + earWidth / 18 - 20, rightEarCenterY + earHeight / 2 + 1, NULL);
    LineTo(hdc, rightEarCenterX + earWidth / 18 + 20, rightEarCenterY + earHeight / 2 + 1);


    // �� �׸���
    HBRUSH eyeBrush = CreateSolidBrush(RGB(0, 0, 0)); // �� ����
    SelectObject(hdc, eyeBrush);

    //���� ��
    Ellipse(hdc, leftEarCenterX - earWidth / 25 - 10, leftEarCenterY + earHeight / 1.8 + 5,
        leftEarCenterX - earWidth / 25 + 10, leftEarCenterY + earHeight / 1.8 + 20);

    //������ ��
    Ellipse(hdc, rightEarCenterX + earWidth / 25 - 10, rightEarCenterY + earHeight / 1.8 + 5,
        rightEarCenterX + earWidth / 25 + 10, rightEarCenterY + earHeight / 1.8 + 20);

    // �� �׸���
    HBRUSH noseBrush = CreateSolidBrush(RGB(0, 0, 0));  // �� ����
    SelectObject(hdc, noseBrush);

    int noseRadius = 7;  // Adjust the radius of the nose as needed

    Chord(hdc, centerX - noseRadius, centerY - noseRadius, centerX + noseRadius, centerY + noseRadius, 0, 0, 0, 0);

    // �� ����Ʈ �׸���
    HBRUSH cheekBrush = CreateSolidBrush(RGB(255, 255, 255)); // �� ����Ʈ ����
    SelectObject(hdc, cheekBrush);

    int cheekRadius = 20;  // Adjust the radius of the cheeks as needed

    // ���� ��
    Chord(hdc, centerX - noseRadius - cheekRadius - 7, centerY + noseRadius - 7, centerX - noseRadius + 7, centerY + noseRadius + cheekRadius + 7, 0, 0, 0, 0);

    // ������ ��
    Chord(hdc, centerX + noseRadius - 7, centerY + noseRadius - 7, centerX + noseRadius + cheekRadius + 7, centerY + noseRadius + cheekRadius + 7, 0, 0, 0, 0);

    //// ���ҽ� ����
    DeleteObject(earBrush);
    DeleteObject(faceBrush);
    DeleteObject(browPen);
    DeleteObject(eyeBrush);
    DeleteObject(noseBrush);
    DeleteObject(cheekBrush);
}