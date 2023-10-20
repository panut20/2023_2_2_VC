#include <windows.h>


// 박스를 나타내는 변수
bool rectwrite = false;
bool triangle = false;
bool Circle = false;
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT triangleVertices[3] = { {0, 0}, {0, 0}, {0, 0} };
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;
int checkrect = 0;
int left, top, bottom, right;
RECT rect = { 0 };

bool PtInPolygon(POINT p);

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            // 첫 번째 버튼 클릭
            rectwrite = true;
            triangle = false;
            Circle = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (LOWORD(wParam) == 2) {
            // 두 번째 버튼 클릭
            rectwrite = false;
            triangle = true;
            Circle = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (LOWORD(wParam) == 3) {
            // 두 번째 버튼 클릭
            triangle = false;
            rectwrite = false;
            Circle = true;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;

    case WM_LBUTTONDOWN:
        // 사각형
        if (rectwrite)
        {
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
            isMouseLButtonPressed = 1;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        //삼각형
        else if (triangle)
        {
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
            isMouseLButtonPressed = 1;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        //원
        else if (Circle) {
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
            isMouseLButtonPressed = 1;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
        
    case WM_LBUTTONUP:
        if (isMouseLButtonPressed)
        {
            //사각형
            if (rectwrite)
            {
                endPoint.x = LOWORD(lParam);
                endPoint.y = HIWORD(lParam);
                isMouseLButtonPressed = 0;
                InvalidateRect(hWnd, NULL, FALSE);
            }
            //삼각형
            else if (triangle) 
            {
                triangleVertices[1].x = LOWORD(lParam);
                triangleVertices[1].y = HIWORD(lParam);
                triangleVertices[2].x = triangleVertices[0].x - (triangleVertices[1].x - triangleVertices[0].x);
                triangleVertices[2].y = triangleVertices[1].y;
                isMouseLButtonPressed = 0;
                InvalidateRect(hWnd, NULL, TRUE);
            }
            //원
            else if (Circle) 
            {
                endPoint.x = LOWORD(lParam);
                endPoint.y = HIWORD(lParam);
                left = min(startPoint.x, endPoint.x);
                top = min(startPoint.y, endPoint.y);
                right = max(startPoint.x, endPoint.x);
                bottom = max(startPoint.y, endPoint.y);
                isMouseLButtonPressed = 0;
                InvalidateRect(hWnd, NULL, TRUE);
            }
        }
        break;

    case WM_MOUSEMOVE:
        if (isMouseLButtonPressed)
        {
            if (rectwrite)
            {
                endPoint.x = LOWORD(lParam);
                endPoint.y = HIWORD(lParam);
                rect.left = min(startPoint.x, endPoint.x);
                rect.top = min(startPoint.y, endPoint.y);
                rect.right = max(startPoint.x, endPoint.x);
                rect.bottom = max(startPoint.y, endPoint.y);

                InvalidateRect(hWnd, NULL, FALSE);
            }
            else if (triangle)
            {
                triangleVertices[0].x = startPoint.x;
                triangleVertices[0].y = startPoint.y;

                triangleVertices[1].x = LOWORD(lParam);
                triangleVertices[1].y = HIWORD(lParam);

                triangleVertices[2].x = triangleVertices[0].x - (triangleVertices[1].x - triangleVertices[0].x);
                triangleVertices[2].y = triangleVertices[1].y;

                InvalidateRect(hWnd, NULL, TRUE);
            }
            else if (Circle) 
            {
                endPoint.x = LOWORD(lParam);
                endPoint.y = HIWORD(lParam);
                left = min(startPoint.x, endPoint.x);
                top = min(startPoint.y, endPoint.y);
                right = max(startPoint.x, endPoint.x);
                bottom = max(startPoint.y, endPoint.y);
                InvalidateRect(hWnd, NULL, TRUE);
            }
        }
        if (isMouseRButtonPressed && checkrect && !IsRectEmpty(&rect)) {
            rect.left += LOWORD(lParam) - startPoint.x;
            rect.top += HIWORD(lParam) - startPoint.y;
            rect.right += LOWORD(lParam) - startPoint.x;
            rect.bottom += HIWORD(lParam) - startPoint.y;
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (isMouseRButtonPressed && PtInPolygon(triangleVertices[0])) {
            triangleVertices[0].x += LOWORD(lParam) - startPoint.x;
            triangleVertices[0].y += HIWORD(lParam) - startPoint.y;
            triangleVertices[1].x += LOWORD(lParam) - startPoint.x;
            triangleVertices[1].y += HIWORD(lParam) - startPoint.y;
            triangleVertices[2].x += LOWORD(lParam) - startPoint.x;
            triangleVertices[2].y = triangleVertices[1].y;
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_RBUTTONDOWN:
    {
        POINT mousePos;
        mousePos.x = LOWORD(lParam);
        mousePos.y = HIWORD(lParam);

        if (PtInRect(&rect, mousePos)) {
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
            isMouseRButtonPressed = 1;
            checkrect = 1;
        }
        else if (PtInPolygon(mousePos)) {
            /*triangleVertices[0].x = LOWORD(lParam);
            triangleVertices[0].y = HIWORD(lParam);*/
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
            isMouseRButtonPressed = 1;
        }
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;

    case WM_RBUTTONUP:
    {
        if (rectwrite) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            isMouseRButtonPressed = 0;
            checkrect = 0;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (triangle) {
            /*triangleVertices[1].x = LOWORD(lParam);
            triangleVertices[1].y = HIWORD(lParam);*/
            isMouseRButtonPressed = 0;
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    break;

    case WM_PAINT:
    {

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        
        if (rectwrite)
        {
            if (!IsRectEmpty(&rect))
            {
                /*FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));*/
                HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
                FillRect(hdc, &rect, hBrush);
                DeleteObject(hBrush);
            }
        }
        else if (triangle)
        {
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
            SelectObject(hdc, hBrush);
            // 삼각형 그리기
            Polygon(hdc, triangleVertices, 3);
            DeleteObject(hBrush);
        }
        else if (Circle) 
        {
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
            SelectObject(hdc, hBrush);
            Chord(hdc, left, top, right, bottom, 0, 0, 0, 0); // 타원 그리기
            DeleteObject(hBrush);
        }
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return S_OK;
}



// 프로그램 진입점
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

    HWND hWnd;
    HWND hButton1, hButton2;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"Win32 Button Example", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"Rect", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 20, 200, 60, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"triangle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 200, 200, 60, hWnd, (HMENU)2, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 400, 200, 60, hWnd, (HMENU)3, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

bool PtInPolygon(POINT p) {
    triangleVertices;
    HRGN hRgn = CreatePolygonRgn(triangleVertices, 3, WINDING);

    bool result = PtInRegion(hRgn, p.x, p.y);
    DeleteObject(hRgn);

    return result;
}