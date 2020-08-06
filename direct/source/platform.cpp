/**
** 系统平台相关支持
*/


#include <windows.h>
#include "../include/platform.h"

#include "../include/log.h"
#include "../include/game.h"

Game *game = nullptr;


//config
const bool FULL_SCREEN = false;
const bool DEBUG = true;
const bool PRINT = true;
const bool RUNLOG = false;

LPCSTR m_applicationName;
HINSTANCE m_hInstance;

HWND m_hwnd;  //Application window句柄

// WINDOWS CALLBACK FUNCTION
static LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void log(const std::string str)
{
	//if (nullptr == str) {
	//	Logger::getInstance()->info("error null str");
	//	return;
	//}
	Logger::get()->log(str);
}

void console(const std::string s)
{
	Logger::get()->print(s);
}

void Startup()
{
	if (game == nullptr)
	{
		game = new Game;
	}
	game->init(DEBUG, PRINT, RUNLOG);
}

void Run()
{
	Logger::get()->log("Application Run Start.");
	MSG msg;
	while (game->isrunning())
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) {
				log("Message Quit.");
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		game->update();
	}

}

void Shutdown()
{
	log("Application shutdown");
	game->exit();
	delete game;
	game = nullptr;
	ShowCursor(true);
	if (FULL_SCREEN) {
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = NULL;
}


LRESULT CALLBACK WndProc(HWND winHandle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		log("Window create.");
		break;
	case WM_DESTROY:
		log("Window destroy.");
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		return 0;
	case WM_CHAR:
		game->inputhandle((char)wParam);
		return 0;
	default:
		break;
	}
	return DefWindowProc(winHandle, msg, wParam, lParam);
}

bool InitWindow(int& screenW, int& screenH)
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
	screenW = GetSystemMetrics(SM_CXSCREEN);
	screenH = GetSystemMetrics(SM_CYSCREEN);


	// 根据是否全屏设置不同的分辨率.
	if (FULL_SCREEN)
	{
		//全屏模式下，设置窗口大小为windows桌面分辨率.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenW;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenH;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// 临时设置显示设备为全屏模式，注意：应用程序退出时候，将恢复系统默认设置。
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// 设置窗口的左上角坐标位置为(0,0).
		posX = posY = 0;
	}
	else
	{
		// 窗口模式：800*600.
		screenW = 800;
		screenH = 600;

		// 窗口左上角坐标位置,posX, posY
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenW) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenH) / 2;
	}

	// 全屏和窗口使用不同的参数.
	if (FULL_SCREEN)
	{
		m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			posX, posY, screenW, screenH, NULL, NULL, m_hInstance, NULL);
	}
	else
	{
		m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
			WS_OVERLAPPEDWINDOW,
			posX, posY, screenW, screenH, NULL, NULL, m_hInstance, NULL);
	}

	// 显示窗口并设置其为焦点.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	ShowCursor(true);

	return true;
}