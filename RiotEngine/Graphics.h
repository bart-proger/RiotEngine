#pragma once
#include <string>
using std::string;
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#ifndef LINK_LIBS_OPENGL
	#define	LINK_LIBS_OPENGL
	#pragma comment(lib, "opengl32.lib")
	#pragma comment(lib, "glu32.lib")
#endif
//#include <SDL2/SDL_rect.h>
//#include "Texture.h"
//#include <map>
// #include "Font.h"

class Graphics
{
public:
	Graphics();
	~Graphics();
	bool init(SDL_Window *, int width, int height);
	void free();

	void begin2D();
	void end2D();

	void drawRect(int x, int y, int w, int h);

private:
	bool initOpenGL();

	SDL_GLContext glContext_;
	int width_, height_;
};

