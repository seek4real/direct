#pragma once

//keyboard input handler

namespace direct {
class KeyBoardInput final
{
public:


	static void onEvent(char);
private:
	KeyBoardInput();
	~KeyBoardInput();
};
}

