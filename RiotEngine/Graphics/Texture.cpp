#include "Texture.h"
#include "../Graphics.h"
#include <SDL2/SDL_image.h>

bool Texture::loadFromFile(string fileName, void *params /*= nullptr*/)
{
	if (loaded_)
		free();

	SDL_Surface *surface;

	if (!(surface = IMG_Load(fileName.c_str())))
	{
		SDL_Log("[error] Unable to load image from \"%s\". SDL Error: %s\n", fileName.c_str(), IMG_GetError());
		return false;
	}

	if ((surface->h & (surface->h - 1)) != 0 || (surface->w & (surface->w - 1)) != 0)
	{
		SDL_Log("[warning] Resolution of \"%s\" is not a power of 2\n", fileName.c_str());
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

	GLuint id;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, bpp, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

	/* Linear Filtering */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
// 
// 	GLenum error = GL_NO_ERROR;
// 	error = glGetError();
// 	if (error != GL_NO_ERROR)
// 	{
// 		SDL_Log("[error] OpenGL Error: %s\n", gluErrorString(error));
// 		SDL_FreeSurface(surface);
// 		return false;
// 	}

	id_ = id;
	width_ = surface->w;
	height_ = surface->h;

	SDL_FreeSurface(surface);
	return (loaded_ = true);
}

void Texture::free()
{
	if (id_)
		glDeleteTextures(1, &id_);
	
	loaded_ = false;
}
