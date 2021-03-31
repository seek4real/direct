/**
** ϵͳƽ̨���֧��
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

HWND m_hwnd;  //Application window���
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
			//ת�����ټ�
			TranslateMessage(&msg);

			//����Ϣ���͸�windows proc(������WndProc)
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
	wc.lpfnWndProc = WndProc; //ָ���ص�����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //Ĭ�Ϻ�ɫ���ں�ɫ����
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// ע�ᴰ���� 
	RegisterClassEx(&wc);


	// �õ�windows����ֱ���
	int _screenW = GetSystemMetrics(SM_CXSCREEN);
	int _screenH = GetSystemMetrics(SM_CYSCREEN);


	// �����Ƿ�ȫ�����ò�ͬ�ķֱ���.
	if (isFullScreen)
	{
		//ȫ��ģʽ�£����ô��ڴ�СΪwindows����ֱ���.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)_screenW;
		dmScreenSettings.dmPelsHeight = (unsigned long)_screenH;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// ��ʱ������ʾ�豸Ϊȫ��ģʽ��ע�⣺Ӧ�ó����˳�ʱ�򣬽��ָ�ϵͳĬ�����á�
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// ���ô��ڵ����Ͻ�����λ��Ϊ(0,0).
		posX = posY = 0;
	}
	else
	{
		// ����ģʽ
		//_screenW = screenW;
		//_screenH = screenH;

		// �������Ͻ�����λ��,posX, posY
		posX = (GetSystemMetrics(SM_CXSCREEN) - _screenW) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - _screenH) / 2;
	}

	// ȫ���ʹ���ʹ�ò�ͬ�Ĳ���.
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

	// ��ʾ���ڲ�������Ϊ����.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	ShowCursor(true);

	return true;
}