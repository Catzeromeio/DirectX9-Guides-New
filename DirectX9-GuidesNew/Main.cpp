#include "stdafx.h"
#include "D3DUtility.h"
#include "BasicSample.h"

using namespace d3d;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	//register the window class
	const wchar_t CLASS_NAME[] = L"DirectX9 Guides Window Class";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	//create the window
	HWND hwnd = CreateWindowEx
	(
		0,
		CLASS_NAME,
		L"Learn to program windows",
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		0, 0, ScreenHight, ScreenWeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	BasicSample theSample =  BasicSample();
	theSample.InitD3D(hwnd);
	theSample.SetUp();

	static float lastTime = (float)timeGetTime();

	//run the message loop
	MSG msg = {};
	while (true)
	{
		float currentTime = (float)timeGetTime();

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
		theSample.CleanUp();
			return 0;
		}

		float deltaTime = (currentTime - lastTime)*0.001f;
		theSample.Display(deltaTime);

		lastTime = currentTime;
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		//FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
		return 0;
	}
	default:
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}
