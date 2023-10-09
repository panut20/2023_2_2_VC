﻿#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;
RECT rect = { 0 }; // 현재 그려진 사각형의 위치와 크기를 저장합니다.
RECT savedRect = { 0 }; // 이동하기 전의 사각형의 위치와 크기를 저장합니다.

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);

		// 기존에 그려진 사각형을 지우기 위해 화면을 흰색으로 칠함.
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);
		FillRect(hdc, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));

		///** 사각형 그리기
		//*/
		//HDC hdc = GetDC(hwnd);
		//RECT rect = { 50, 50, 150, 150 }; // 왼쪽 상단 좌표 (50, 50)에서 오른쪽 하단 좌표 (150, 150)까지의 사각형
		//HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // 핑크 브러시 생성

		//if (hBrush == NULL)
		//{
		//	MessageBox(NULL, L"CreateSolidBrush failed!", L"Error", MB_ICONERROR);
		//	exit(-1);	//예외
		//}

		//// 그리기
		//FillRect(hdc, &rect, hBrush); // 사각형을 빨간색으로 채우기
		//ReleaseDC(hwnd, hdc);

		startPoint.x = LOWORD(lParam);
		startPoint.y = HIWORD(lParam);
		isMouseLButtonPressed = 1;
	}
	break;

	//강의에 안나왔지만 마우스가 움직일때의 이벤트를 뜻합니다.
	case WM_MOUSEMOVE:
	{
		// 마우스 이동 중
		if (isMouseLButtonPressed)
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);

			// WM_PAINT 메시지를 유발하여 사각형을 화면에 그립니다.
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);

		isMouseLButtonPressed = 0;

		// WM_PAINT 메시지를 유발하여 네모를 화면에 그림.
		InvalidateRect(hwnd, NULL, TRUE);

		// 추가된 부분: 그림을 그리는 코드
		HDC hdc = GetDC(hwnd);
		RECT rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // 핑크 브러시 생성

		if (hBrush == NULL)
		{
			MessageBox(NULL, L"CreateSolidBrush failed!", L"Error", MB_ICONERROR);
			exit(-1);
		}

		FillRect(hdc, &rect, hBrush);
		ReleaseDC(hwnd, hdc);
	}

	case WM_RBUTTONDOWN:
	{

	}
	break;

	case WM_RBUTTONUP:
	{

	}
	break;

	case WM_PAINT:
	{
		HDC hdc = GetDC(hwnd);

		if (isMouseLButtonPressed)
		{
			RECT rect = { min(startPoint.x, endPoint.x), min(startPoint.y, endPoint.y), max(startPoint.x, endPoint.x), max(startPoint.y, endPoint.y) };
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
		}

		ReleaseDC(hwnd, hdc);

	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("202007061 백종빈"),
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,	// 창의 크기를 변경할 수 있는 테두리 삭제
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
		);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.



	// 메시지 처리 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		{

			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	//종료 메시지 보내기
	return (int)msg.wParam;

}