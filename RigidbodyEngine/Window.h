#pragma once
#include <Windows.h>
#include <string>

/*
Window Class:
- Generic window class to package win32 window creation
- Full initialization order is construct, register, create, show, and update
*/
class Window
{
public:
	Window() = default;
	/*
	Parameters:
	@const char* - name of the window
	@WNDCLASSEX - data defintion for the window to be created
	*/
	Window(const char*, WNDCLASSEX);
	/*
	Parameters:
	@WNDCLASSEX - data defintion for the window to be created
	*/
	Window(WNDCLASSEX);
	virtual ~Window() = default;

	/*
	Use:
	- Extended classes with WNDCLASSEX defined in constructor
	  and default constructor

	Precondition(s):
	- Use before registration

	Postcondition(s):
	- Sets the WNDCLASSEX for registration and creation
	*/
	void SetWndClass(WNDCLASSEX);
	/*
	Returns:
	@BOOL - true if successful window registration
	*/
	BOOL Register();
	/*
	Returns:
	@BOOL - true if successful window creation
	*/
	BOOL Create(DWORD, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
	/*
	Returns:
	@BOOL - true if previous state was visible
	        false if previous state was invisible
	*/
	BOOL Show(HWND, int);
	/*
	Returns:
	@BOOL - true if successful update
	*/
	BOOL Update(HWND);
	/*
	Returns:
	@HWND - a handle to the window
	*/
	HWND GetHwnd();
private:
	WNDCLASSEX mWndClass;
	HWND mHWnd;
};