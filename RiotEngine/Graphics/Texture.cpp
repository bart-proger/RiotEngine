#include "Texture.h"
#include "../Graphics.h"
#include <SDL2/SDL_image.h>

bool Texture::loadFromFile(string fileName, void *params /*= nullptr*/)
{
	SDL_Surface *surface;

	if (!(surface = IMG_Load(fileName.c_str())))
	{
		SDL_Log("[error] Unable to load image from \"%s\". SDL Error: %s\n", fileName.c_str(), IMG_GetError());
		return false;
	}

	GLint bpp = surface->format->BytesPerPixel;
	GLenum format;

	switch (bpp)
	{
		case 4:
			if (surface->format->Rmask == 0x000000ff)
				format = GL_RGBA;
			else
				format = GL_BGRA;
			break;
		case 3:
			if (surface->format->Rmask == 0x000000ff)
				format = GL_RGB;
			else
				format = GL_BGR;
			break;
			// 		case 1:
			// 			format = GL_LUMINANCE;
			// 			break;
		default:
			SDL_Log("[error] Unknown image format \"%s\"\n", fileName.c_str());
			SDL_FreeSurface(surface);
			return false;
	}

	if (!createFromPixels(surface->w, surface->h, bpp, format, surface->pixels))
 	{
 		SDL_FreeSurface(surface);
 		return false;
 	}

	SDL_FreeSurface(surface);
	return (loaded_ = true);
}

void Texture::free()
{
	if (id_)
		glDeleteTextures(1, &id_);
	id_ = 0;
	width_ = 0;
	height_ = 0;
	
	loaded_ = false;
}

bool Texture::createFromPixels(GLsizei width, GLsizei height, GLint bpp, GLenum format, GLvoid *pixels, GLint filter /*= GL_LINEAR*/, GLint wrap /*= GL_CLAMP_TO_EDGE*/)
{
	if ((height & (height - 1)) != 0 || (width & (width - 1)) != 0)
	{
		SDL_Log("[warning] Texture resolution is not a power of 2\n");
	}
	if (!pixels)
	{
		SDL_Log("[error] Texture pixels missing!\n");
		return false;
	}

	GLuint id;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, bpp, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	/* Linear Filtering */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

	glBindTexture(GL_TEXTURE_2D, 0);

	GLenum error = GL_NO_ERROR;
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		SDL_Log("[error] Could not create texture! OpenGL Error: %s\n", gluErrorString(error));
		return false;
	}

	if (loaded_)
		free();

	id_ = id;
	width_ = width;
	height_ = height;

	return (loaded_ = true);
}
