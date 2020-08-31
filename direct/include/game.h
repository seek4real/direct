//game.h


#pragma once


namespace direct {

class Game
{
public:
	static auto instance()->Game&;
	void init(bool debug, bool print, bool runlog);
	void update();
	void display();
	void exit();

	bool isrunning();
	void stop();
private:
	bool running;
	bool debug;

	Game();
	~Game();
	Game(const Game&);
	Game& operator=(const Game&);
};
}