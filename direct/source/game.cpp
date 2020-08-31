//game.cpp

#include "../include/game.h"
#include "../include/log.h"
#include "../include/msg.h"

using direct::Game;
using direct::Msg;


//Default constructor
Game::Game():running(false), debug(false)
{
	Msg* msg = new Msg(Cmd_GameCreate, "game construct.");
}

//Copy constructor
Game::Game(const Game&) : running(false), debug(false){}

//Assign constructor
Game& Game::operator =(const Game& g)
{
	console("Game Assign.");

	this->running = g.running;
	this->debug = g.debug;

	return *this;
}

Game::~Game()
{
	Msg* msg = new Msg(Cmd_GameDestroy, "game desctruct.");
}

/**
** C++11 新特性 返回类型后置
** 原来的写法 Game& Game::instance() { return *this; }
*/
auto Game::instance() -> Game&
{
	//console("Game get instance");
	static Game game;
	return game;
}

void Game::init(bool _debug, bool print, bool runlog)
{
	running = true;
	Logger::get()->log("Init Game.");
}




/**
** Update game logic.
*/
void Game::update()
{
	//Logger::get()->log("Game Update.");
}

/**
** Update game display.
*/
void Game::display()
{

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