

/**
** ϵͳƽ̨���֧��
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
		windows��Ϸ��ѭ��
	*/
	bool loop();
private:
	int winWidth;
	int winHeight;
	bool isFullScreen;
};


}