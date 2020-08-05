/*
* keyboard.h
*/
#include "../include/keyboard.h"
#include "../include/msg.h"
#include "../include/log.h"
#include "../include/game.h"

extern Game *game;

KeyBoardInput::KeyBoardInput()
{
}

KeyBoardInput::~KeyBoardInput()
{
}


void KeyBoardInput::onEvent(char key)
{
	std::string _input = "key_";
	_input += toascii(key);
	Logger::get()->print(_input);
	Logger::get()->log(_input);

	Msg* msg;
	switch (key)
	{
	//case VK_ESCAPE:break;
	case 0x1B:
		msg = new Msg(Cmd_Shutdown, "shutdown now.");
		if (!msg) {
			return;
		}
		delete  msg;
		msg = nullptr;
		game->stop();
		break;
	default:
		break;
	}
}