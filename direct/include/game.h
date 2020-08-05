//game.h


#pragma once



class Game
{
public:
	Game();
	~Game();
	void init(bool debug, bool print, bool runlog);
	void update();
	void inputhandle(char);
	void exit();

	bool isrunning();
	void stop();
private:
	bool running;
	bool debug;
};