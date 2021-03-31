/*
* keyboard.cpp
* 处理Windows系统键盘消息。
* 转换消息为逻辑状态
*/
#include "../include/keyboard.h"
#include "../include/msg.h"
#include "../include/log.h"
#include "../include/game.h"

#include <WinUser.h>

using direct::KeyBoardInput;
using direct::Game;
using direct::Logger;
using direct::Msg;
using direct::Command;

KeyBoardInput::KeyBoardInput()
{
}

KeyBoardInput::~KeyBoardInput()
{
}


void KeyBoardInput::onWinKeyDown(char key)
{
	std::string _input = "key_";
	_input += toascii(key);
	Logger::get()->print(_input);
	Logger::get()->log(_input);

	Msg* msg;
	switch (key)
	{
	case VK_ESCAPE:
	//case 0x1B:
		msg = new Msg(Command::Cmd_Shutdown, "shutdown now.");
		if (!msg) {
			return;
		}
		delete  msg;
		msg = nullptr;
		//TODO 暂时直接关闭，之后改成发送事件消息
		Game::instance().stop();
		break;
	default:
		break;
	}
}

void KeyBoardInput::onWinKeyUp(char key)
{

}