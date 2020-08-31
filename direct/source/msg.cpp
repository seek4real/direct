/*
** msg.cpp
** game message
*/

#include "../include/msg.h"
#include "../include/log.h"

using direct::Msg;
using direct::Command;

Msg::Msg(Command _cmd, std::string _desc) :cmd(_cmd), desc(_desc)
{
	std::string out = "MESSAGE:" + desc;
	Logger::get()->print(out);
}

Msg::~Msg()
{
	Logger::get()->print("Msg delete");
}