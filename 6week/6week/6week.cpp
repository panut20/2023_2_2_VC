//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif

#include <windows.h>
#define ID_TIMER 1

POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isKeyPressed = 0;
int moveSpeed = 1; // 작은 네모의 이동 속도
RECT rect;

RECT rect_user = { 5, 5, 15, 15 }; // 왼쪽 상단 좌표 (5, 5)에서 오른쪽 하단 좌표 (15, 15)까지의 사각형	left, top, right ,bottom
RECT rect_target = { 50, 50, 150, 150 }; // 왼쪽 상단 좌표 (50, 50)에서 오른쪽 하단 좌표 (150, 150)까지의 사각형

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hwnd);
	
	HBRUSH hBrush_user = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH hBrush_target = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH hBrush_eraser = CreateSolidBrush(RGB(255, 255, 255));
	const wchar_t* text = L"Crash!!!";

	switch (uMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, ID_TIMER, 16, NULL); // 타이머 시작 (약 60fps)
		break;

	case WM_KEYDOWN:
		isKeyPressed = 1;

		if (wParam == VK_RIGHT)
		{
			rect_user.left += 5;
			rect_user.right += 5;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (wParam == VK_LEFT)
		{
			rect_user.left -= 5;
			rect_user.right -= 5;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (wParam == VK_UP)
		{
			rect_user.top -= 5;
			rect_user.bottom -= 5;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (wParam == VK_DOWN)
		{
			rect_user.top += 5;
			rect_user.bottom += 5;
			InvalidateRect(hwnd, NULL, TRUE);
		}

		break;

	case WM_KEYUP:
		isKeyPressed = 0;
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// 배경을 흰색으로 지웁니다.
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		if (IntersectRect(&rect, &rect_user, &rect_target))
		{
			TextOut(hdc, 10, 10, text, lstrlen(text));
			FillRect(hdc, &rect_target, hBrush_target);
			FillRect(hdc, &rect_user, hBrush_user);
		}

		if (isKeyPressed)
		{
			FillRect(hdc, &rect_target, hBrush_target);
			FillRect(hdc, &rect_user, hBrush_user);
		}
		else
		{
			FillRect(hdc, &rect_target, hBrush_target);
			FillRect(hdc, &rect_user, hBrush_user);
		}
		EndPaint(hwnd,&ps);
	}
	break;

	case WM_TIMER:
		if (isKeyPressed) {
			if (wParam == ID_TIMER) {
				if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {		// GetAsyncKeyState 함수를 사용하여 특정 키가 눌려 있는지 확인하고, 눌려 있다면 해당 방향으로 작은 네모를 이동시킵니다.
																// GetAsyncKeyState(VK_RIGHT)는 오른쪽 화살표 키의 현재 상태를 반환합니다. 반환값은 16비트 숫자로, 비트 15에서는 키가 현재 눌려있는지 여부를 나타냅니다. 즉, 비트 15가 1이면 키가 눌려져 있는 상태입니다.
																// &0x8000은 비트 연산을 통해 비트 15만을 확인하는 것입니다. 0x8000은 16진수로 15번째 비트가 1인 값을 나타냅니다.
					rect_user.left += moveSpeed; // 오른쪽으로 이동
					rect_user.right += moveSpeed;
				}
				if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
					rect_user.left -= moveSpeed; // 왼쪽으로 이동
					rect_user.right -= moveSpeed;
				}
				if (GetAsyncKeyState(VK_UP) & 0x8000) {
					rect_user.top -= moveSpeed; // 위로 이동
					rect_user.bottom -= moveSpeed;
				}
				if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
					rect_user.top += moveSpeed; // 아래로 이동
					rect_user.bottom += moveSpeed;
				}

				InvalidateRect(hwnd, NULL, TRUE);
			}
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	DeleteObject(hBrush_user);
	DeleteObject(hBrush_target);
	DeleteObject(hBrush_eraser);
	ReleaseDC(hwnd, hdc);

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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 150, 100, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("202007061 백종빈"),
		WS_OVERLAPPEDWINDOW, 
		0, 0,
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

	// 메시지 처리.
	while (msg.message != WM_QUIT)
	{
		if (GetMessage(&msg, NULL, 0, 0))
		{
			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);
		}
		//if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//{
		//	// 메시지 해석해줘.
		//	TranslateMessage(&msg);
		//	// 메시지를 처리해야할 곳에 전달해줘.
		//	DispatchMessage(&msg);
		//} // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		//else{}
	}

	UnregisterClass(wc.lpszClassName, wc.hInstance);

	//종료 메시지 보내기
	return (int)msg.wParam;

}
