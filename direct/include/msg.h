/*
* command.h
*/
#pragma once

#include <string>


namespace direct
{
	enum Command
	{
		Cmd_Null = 0,
		Cmd_GameCreate,
		Cmd_GameDestroy,
		Cmd_Shutdown,
	};


	class Msg
	{
	public:

		Msg(Command, std::string);
		~Msg();

	private:
		Command cmd;
		std::string desc;
	};
}

