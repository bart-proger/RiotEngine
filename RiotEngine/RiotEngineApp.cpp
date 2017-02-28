#include "RiotEngineApp.h"
#include <iostream>

RiotEngineApp::RiotEngineApp():
window_(nullptr) 
{
}

RiotEngineApp::~RiotEngineApp()
{
	SDL_Quit();
}

bool RiotEngineApp::init(string title, int width, int height)
{
	//Initialize SDL subsystems
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s", SDL_GetError());
		return false;
	}
	//Create window
	if (!(window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
										width, height, SDL_WINDOW_SHOWN)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s", SDL_GetError());
		return false;
	}
	//Create renderer for window
	if (graphics_.init(window_))
	{
		width_ = width;
		height_ = height;

		return onInit();
	}
	return false;
}

void RiotEngineApp::free()
{
	onFree();

	graphics_.free();
	if (window_)
	{
		SDL_DestroyWindow(window_);
		window_ = nullptr;
	}
}

void RiotEngineApp::run()
{
	SDL_Event e;
	bool quit = false;

	while(!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else 
			{
				switch (e.type)
				{
					case SDL_KEYDOWN:
						onKeyDown(e.key.keysym.sym);
						break;
					case SDL_MOUSEBUTTONDOWN:
						onPress({ e.button.x, e.button.y });
						break;
					case SDL_FINGERDOWN:
						onPress({ (int)(e.tfinger.x * width_), (int)(e.tfinger.y * height_) });
						break;
					case SDL_MOUSEBUTTONUP:
						onRelease({ e.button.x, e.button.y });
						break;
					case SDL_FINGERUP:
						onRelease({ (int)(e.tfinger.x * width_), (int)(e.tfinger.y * height_) });
						break;
					case SDL_MOUSEMOTION:
						onMove({ e.motion.x, e.motion.y });
						break;
					case SDL_FINGERMOTION:
						onMove({ (int)(e.tfinger.x * width_), (int)(e.tfinger.y * height_) });
						break;
				}
			}
		}

		onUpdate();
		onDraw();

        graphics_.present();
	}
	free();
}

void RiotEngineApp::quit()
{
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}

