#include "GameWindow.h"

unsigned int GameWindow::WIDTH = 1920;
unsigned int GameWindow::HEIGHT = 1080;

GameWindow::GameWindow(const char* windowName, HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;//sizeof(std::shared_ptr<InputController>);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_HAND);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = windowName;

	SetWndClass(wc);
}

GameWindow::GameWindow(WNDCLASSEX wndClass)
	: Window::Window(wndClass) {}

BOOL GameWindow::Create(HINSTANCE hInstance)
{
	BOOL result;
	if (HEIGHT != 0 && WIDTH != 0)
	{
		 result = Window::Create(NULL,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			WIDTH, HEIGHT,
			NULL,
			NULL,
			hInstance,
			NULL);
		return result;
	}
	result = Window::Create(NULL,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		512, 512,
		NULL,
		NULL,
		hInstance,
		NULL);
	//SetWindowLongPtr(GetHwnd(), 0, (LONG)&*mInputController);
	return result;
}

long CALLBACK GameWindow::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		ValidateRect(hWnd, NULL);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		return 0;
	case WM_KEYUP:
		return 0;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
}