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

class Texture;

class Graphics
{
public:
	Graphics();
	~Graphics();
	bool init(SDL_Window *window, int width, int height);
	void free();

	void begin2D();
	void end2D();

	void drawTexture(const Texture &, int x, int y);
	void drawRect(int x, int y, int w, int h);

	int width() const { return width_; }
	int height() const { return height_; }

private:
	bool initOpenGL();
	bool errorOpenGL();

	SDL_GLContext glContext_;
	int width_, height_;
};

