#include <iostream>
#include "_Game.h"
#include <locale>

int SDL_main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	_Game app;

	if (app.init("RiotEngine demo game", 1280, 720))
	{
		app.run();
	}
	else
		system("pause");

	return 0;
}