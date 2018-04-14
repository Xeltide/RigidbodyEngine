#include <Windows.h>
#include <iostream>
#include <chrono>

#include "GameEngine.h"
#include "GameWindow.h"

using namespace std::chrono;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pstrCmdLine, int iCmdShow)
{
	MSG msg;
	GameEngine* engine = new GameEngine();
	GameWindow* window = new GameWindow("RigidbodyEngine", hInstance);

	if (!window->Register())
	{
		OutputDebugString("Error: Window registration failed.\n");
		// TODO: Error message and close
	}

	if (!window->Create(hInstance))
	{
		OutputDebugString("Error: Window creation failed.\n");
		// TODO: Error message and close
	}

	window->Show(window->GetHwnd(), iCmdShow);

	if (!window->Update(window->GetHwnd()))
	{
		OutputDebugString("Error: Window update failed.\n");
		// TODO: Error message and close
	}

	engine->Initialize(window->GetHwnd(), window->WIDTH, window->HEIGHT);

	auto start = high_resolution_clock::now();
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			auto end = high_resolution_clock::now();
			auto dt = end - start;
			start = high_resolution_clock::now();
			engine->Update(dt.count() / 1000000000.0);
		}
	}

	delete engine;
	delete window;
	return msg.wParam;
}