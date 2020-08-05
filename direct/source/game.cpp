//game.cpp

#include "../include/game.h"
#include "../include/log.h"
#include "../include/keyboard.h"
#include "../include/msg.h"

Game::Game():running(false), debug(false)
{
	Msg* msg = new Msg(Cmd_GameCreate, "game construct.");
}

Game::~Game()
{
	Msg* msg = new Msg(Cmd_GameDestroy, "game desctruct.");
}

void Game::init(bool _debug, bool print, bool runlog)
{
	running = true;
	debug = _debug;
	Logger::get()->init(debug, print, runlog);
	Logger::get()->log("Init Game.");
}

void Game::update()
{

}

//´¦Àí
void Game::inputhandle(char c)
{
	KeyBoardInput::onEvent(c);
}

//onExit
void Game::exit()
{
	Logger::get()->log("Exit Game.");
	Logger::get()->release();
}

bool Game::isrunning()
{
	return running;
}

void Game::stop()
{
	running = false;
}