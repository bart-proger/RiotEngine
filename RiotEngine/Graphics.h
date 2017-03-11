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

#include "Graphics/Texture.h"

class Sprite;
class AnimatedSprite;

class Graphics
{
public:
	Graphics(): glContext_(nullptr), width_(0), height_(0) {}

	bool init(SDL_Window *window, int width, int height);
	void free();

	void begin2D();
	void end2D();
	void bindTexture(Texture &);

// 	bool loadTexture(Texture &, string fileName);
// 	void freeTexture(Texture &);
	void drawTexture(Texture &, int x, int y, int w = 0, int h = 0);
	void drawSprite(Sprite &, int x, int y);
	void drawAnimatedSprite(AnimatedSprite &, int x, int y);

	void drawRect(int x, int y, int w, int h);

	int width() const { return width_; }
	int height() const { return height_; }
	Texture & defaultTexture() { return defaultTexture_; }

private:
	bool initOpenGL();
	bool errorOpenGL();

	SDL_GLContext glContext_;
	int width_, height_;

	Texture defaultTexture_;

	Texture *currentTexture_;
};

