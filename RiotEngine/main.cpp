#include <iostream>
#include "RiotEngineApp.h"

int SDL_main(int argc, char** argv)
{
	RiotEngineApp app;

	if (app.init("RiotEngine demo", 640, 480))
	{
		app.run();
	}

	return 0;
}