

/**
** 系统平台相关支持
*/

#pragma once


namespace direct
{
	/**
		Windows platform Application support.
	*/
class _declspec(dllexport) Win32Application
{
public:
	Win32Application();
	~Win32Application();
	

	bool InitWindow(int, int);
	bool Startup();
	void Shutdown();

	/**
		windows游戏主循环
	*/
	bool loop();
private:
	int winWidth;
	int winHeight;
	bool isFullScreen;
};


}