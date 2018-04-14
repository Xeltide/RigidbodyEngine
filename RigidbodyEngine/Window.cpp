#include "Window.h"

Window::Window(const char* wndName, WNDCLASSEX wndClass)
	: mWndClass(wndClass)
{
	mWndClass.lpszClassName = wndName;
}

Window::Window(WNDCLASSEX wndClass)
	: mWndClass(wndClass) {}


void Window::SetWndClass(WNDCLASSEX wndClass)
{
	mWndClass = wndClass;
}

BOOL Window::Register()
{
	if (RegisterClassEx(&mWndClass) != 0)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL Window::Create(DWORD dwExStyle, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	mHWnd = CreateWindowEx(dwExStyle,
		mWndClass.lpszClassName,
		mWndClass.lpszClassName,
		dwStyle,
		x,
		y,
		nWidth,
		nHeight,
		hWndParent,
		hMenu,
		hInstance,
		lpParam);

	if (mHWnd != NULL)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL Window::Show(HWND hWnd, int iCmdShow)
{
	return ShowWindow(hWnd, iCmdShow);
}

BOOL Window::Update(HWND hWnd)
{
	if (UpdateWindow(hWnd) != 0)
	{
		return TRUE;
	}
	return FALSE;
}

HWND Window::GetHwnd()
{
	return mHWnd;
}