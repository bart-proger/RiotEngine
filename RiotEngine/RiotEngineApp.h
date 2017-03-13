#pragma once
#include <SDL2/SDL.h>
#ifndef LINK_LIBS_SDL2
	#define	LINK_LIBS_SDL2
	#pragma comment(lib, "SDL2.lib")
	#pragma comment(lib, "SDL2main.lib")
	#pragma comment(lib, "SDL2_image.lib")
#endif
#include <string>
using std::string;
#include "Graphics.h"
#include "Math/Point2.h"

class RiotEngineApp
{
public:
	RiotEngineApp();
	virtual ~RiotEngineApp();
	bool init(string title, int width, int height);
	void run();
	void quit();

	Graphics & graphics() { return graphics_; }
	//Network & network();
	float frameTime() const { return frameTime_; }

protected:
	virtual bool onInit() { return true; }
	virtual void onFree() {}
	virtual void onUpdate(float dt) {}
	virtual void onDraw(Graphics &) {}
//	virtual void onKeyEvent() {}
	virtual void onPress(Point2 ) {}
//	virtual void onRelease(SDL_Point) {}
//	virtual void onMove(SDL_Point) {}
//	virtual void onKeyDown(SDL_Keycode) {}

private:
	void free();

	SDL_Window *window_;
	Graphics graphics_;
	//Network network_;
	float frameTime_;
};
