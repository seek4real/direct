// main.cpp
// DirectX D3D practice Project

#ifndef WIN32_LEAN_AND_MEAN

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#endif // !WIN32_LEAN_AND_MEAN


#include <windows.h>
#include "../direct/include/win32application.h"
#include "../direct/include/log.h"

#pragma comment(lib, "direct.lib")

static int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int iCmdShow)
{
	direct::Logger::get()->log("entry win main.");
	direct::Win32Application app;
	app.Startup();

	direct::Logger::get()->log("stop win loop.");
	app.Shutdown();

	return 0;
}

