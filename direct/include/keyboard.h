#pragma once

//keyboard input handler

namespace direct {
class KeyBoardInput final
{
public:


	static void onWinKeyDown(char);
	static void onWinKeyUp(char);
private:
	KeyBoardInput();
	~KeyBoardInput();
};
}

