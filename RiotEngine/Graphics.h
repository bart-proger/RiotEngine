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
	bool init(SDL_Window *);
	void free();

	void present(SDL_Window *);

private:
	bool initOpenGL();

	SDL_GLContext glContext_;
};

