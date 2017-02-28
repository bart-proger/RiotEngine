#pragma once
#include "../Resource.h"
#include <SDL2/SDL_opengl.h>
// #include "../Graphics.h"
class Graphics;

class Texture : public Resource
{
	friend class Graphics;
public:
	Texture(): id_(0), width_(0), height_(0) {}

	bool loadFromFile(string fileName, void *params = nullptr) override;
	void free();

private:
	GLuint id_;
	GLsizei width_;
	GLsizei height_;
};

