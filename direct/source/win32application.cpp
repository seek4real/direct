/**
** 系统平台相关支持
*/

#include <string>
#include "../include/win32application.h"
#include "../include/log.h"
#include "../include/game.h"
#include "../include/keyboard.h"
#include "../include/mouse.h"

//#ifdef WIN32
#include <windows.h>
//#endif // WIN32


using direct::Win32Application;
using direct::Logger;
using direct::Game;
using direct::KeyBoardInput;
using direct::MouseInput;

//config
//const bool FULL_SCREEN = false;
const int screenW = 800;
const int screenH = 600;
const bool DEBUG = true;
const bool PRINT = true;
const bool RUNLOG = true;

LPCSTR m_applicationName;
HINSTANCE m_hInstance;

HWND m_hwnd;  //Application window句柄
MSG msg;

// WINDOWS CALLBACK FUNCTION
static LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



Win32Application::Win32Application():winWidth(0), winHeight(0), isFullScreen(false)
{
}

Win32Application::~Win32Application()
{
}




bool Win32Application::Startup()
{
	Game::instance().init(DEBUG, PRINT, RUNLOG);
	this->InitWindow(screenW, screenH);
	return this->loop();
}


void Win32Application::Shutdown()
{
	Logger::get()->log("Application shutdown");
	ShowCursor(true);
	if (isFullScreen) {
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = NULL;
}


/**
** Game Main Loop.
*/
bool Win32Application::loop()
{
	Logger::get()->log("Application Run Loop.");

	Game* ptrGame = &Game::instance();
	while (ptrGame->isrunning())
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//转换加速键
			TranslateMessage(&msg);

			//将消息发送给windows proc(这里是WndProc)
			DispatchMessage(&msg);
		}
		ptrGame->update();
		ptrGame->display();
	}
	return true;
}


LRESULT CALLBACK WndProc(HWND winHandle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		console("Window create.");
		break;
	case WM_DESTROY:
		console("Window destroy.");
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		KeyBoardInput::onWinKeyDown((char)wParam);
		return 0;
	case WM_LBUTTONDOWN:
		MouseInput::single().onLeftKeyDown(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_RBUTTONDOWN:
		MouseInput::single().onRightKeyDown(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_LBUTTONUP:
		MouseInput::single().onLeftKeyUp(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_RBUTTONUP:
		MouseInput::single().onRightKeyUp(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_MOUSEWHEEL:
		return 0;
	case WM_CHAR:
		return 0;
	//default:
	//	break;
	}
	return DefWindowProc(winHandle, msg, wParam, lParam);
}

bool Win32Application::InitWindow(int screenW, int screenH)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	m_hInstance = GetModuleHandle(NULL);
	m_applicationName = "DirectXEngine";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc; //指定回调函数
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //默认黑色窗口黑色背景
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// 注册窗口类 
	RegisterClassEx(&wc);


	// 得到windows桌面分辨率
	int _screenW = GetSystemMetrics(SM_CXSCREEN);
	int _screenH = GetSystemMetrics(SM_CYSCREEN);


	// 根据是否全屏设置不同的分辨率.
	if (isFullScreen)
	{
		//全屏模式下，设置窗口大小为windows桌面分辨率.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)_screenW;
		dmScreenSettings.dmPelsHeight = (unsigned long)_screenH;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// 临时设置显示设备为全屏模式，注意：应用程序退出时候，将恢复系统默认设置。
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// 设置窗口的左上角坐标位置为(0,0).
		posX = posY = 0;
	}
	else
	{
		// 窗口模式
		//_screenW = screenW;
		//_screenH = screenH;

		// 窗口左上角坐标位置,posX, posY
		posX = (GetSystemMetrics(SM_CXSCREEN) - _screenW) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - _screenH) / 2;
	}

	// 全屏和窗口使用不同的参数.
	if (isFullScreen)
	{
		m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			posX, posY, _screenW, _screenH, NULL, NULL, m_hInstance, NULL);
	}
	else
	{
		m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
			WS_OVERLAPPEDWINDOW,
			posX, posY, _screenW, _screenH, NULL, NULL, m_hInstance, NULL);
	}

	// 显示窗口并设置其为焦点.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	ShowCursor(true);

	return true;
}