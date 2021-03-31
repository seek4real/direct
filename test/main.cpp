// main.cpp
// DirectX D3D practice Project

#ifndef WIN32_LEAN_AND_MEAN

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#endif // !WIN32_LEAN_AND_MEAN


#include <windows.h>
#include "../direct/include/win32application.h"
#include "../direct/include/log.h"

#pragma comment(lib, "direct.lib")

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int iCmdShow)
{
	direct::Logger::get()->log("entry win main.");
	direct::Win32Application app;
	app.Startup();

	return 0;
}

