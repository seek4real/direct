/**
** ϵͳƽ̨���֧��
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

HWND m_hwnd;  //Application window���

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
	screenW = GetSystemMetrics(SM_CXSCREEN);
	screenH = GetSystemMetrics(SM_CYSCREEN);


	// �����Ƿ�ȫ�����ò�ͬ�ķֱ���.
	if (FULL_SCREEN)
	{
		//ȫ��ģʽ�£����ô��ڴ�СΪwindows����ֱ���.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenW;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenH;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// ��ʱ������ʾ�豸Ϊȫ��ģʽ��ע�⣺Ӧ�ó����˳�ʱ�򣬽��ָ�ϵͳĬ�����á�
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// ���ô��ڵ����Ͻ�����λ��Ϊ(0,0).
		posX = posY = 0;
	}
	else
	{
		// ����ģʽ��800*600.
		screenW = 800;
		screenH = 600;

		// �������Ͻ�����λ��,posX, posY
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenW) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenH) / 2;
	}

	// ȫ���ʹ���ʹ�ò�ͬ�Ĳ���.
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

	// ��ʾ���ڲ�������Ϊ����.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	ShowCursor(true);

	return true;
}