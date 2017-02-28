#include <iostream>
#include "_Game.h"

int SDL_main(int argc, char** argv)
{
	_Game app;

	if (app.init("RiotEngine demo game", 640, 480))
	{
		app.run();
	}

	return 0;
}