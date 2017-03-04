#pragma once
#include "../Resource.h"
#include <SDL2/SDL_opengl.h>

class Graphics;

class Texture : public Resource
{
	friend class Graphics;
public:
	Texture(): id_(0), width_(0), height_(0) {}

	bool loadFromFile(string fileName, void *params = nullptr) override;
	void free() override;

	bool createFromPixels(GLsizei width, GLsizei height, GLint bpp, GLenum format, GLvoid *pixels, GLint filter = GL_LINEAR, GLint wrap = GL_CLAMP_TO_EDGE);

	int width() const { return width_; }
	int height() const { return height_; }

private:
	GLuint id_;
	GLsizei width_,  height_;
};

