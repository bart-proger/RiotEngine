#include "Graphics.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "Graphics/Texture.h"

bool Graphics::init(SDL_Window *window, int width, int height)
{
	glContext_ = SDL_GL_CreateContext(window); 
	if (!glContext_)
	{
		SDL_Log("[error] OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	//Use Vsync
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		SDL_Log("[warning] Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}
	//Initialize OpenGL
	if (!initOpenGL())
	{
		return false;
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		SDL_Log("[error] SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	width_ = width;
	height_ = height;

	//Initialize SDL_ttf
// 	if (TTF_Init() == -1)
// 	{
// 		std::cerr << "[error] SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
// 		return false;
// 	}

	GLbyte dtp[] =	{	0x00,  0xff, 0x00, 0xff, 
						0xff,  0x00, 0xff, 0x00,
						0x00,  0xff, 0x00, 0xff,
						0xff,  0x00, 0xff, 0x00  };
	defaultTexture_.createFromPixels(4, 4, 1, GL_LUMINANCE, dtp, GL_NEAREST);

	return true;
}

void Graphics::free()
{
	if (glContext_)
	{
		SDL_GL_DeleteContext(glContext_);
		glContext_ = nullptr;
	}

	//	TTF_Quit();
	IMG_Quit();
}

bool Graphics::initOpenGL()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClearDepth(1.f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLenum error = GL_NO_ERROR;
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		SDL_Log("[error] Error initializing OpenGL! %s\n", gluErrorString(error));
		return false;
	}

	return true;
}

bool Graphics::errorOpenGL()
{
	GLenum error = GL_NO_ERROR;
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		SDL_Log("[error] OpenGL Error: %s\n", gluErrorString(error));
		return true;
	}
	return false;
}

void Graphics::begin2D()
{
	//  glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, width_, height_, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void Graphics::end2D()
{
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	//	glPopAttrib();
}

void Graphics::drawTexture(const Texture &t, int x, int y, int w /*= -1*/, int h /*= -1*/)
{
	if (w < 0)
		w = t.width_;
	if (h < 0)
		h = t.height_;

	glBindTexture(GL_TEXTURE_2D, t.id_);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2i(x, y);
		glTexCoord2f(0, 1); glVertex2i(x, y + h);
		glTexCoord2f(1, 1); glVertex2i(x + w, y + h);
		glTexCoord2f(1, 0); glVertex2i(x + w, y);
	glEnd();
}

Texture & Graphics::defaultTexture()
{
	return defaultTexture_;
}

void Graphics::drawRect(int x, int y, int w, int h)
{
	glBegin(GL_LINE_LOOP);
		glVertex2i(x, y);
		glVertex2i(x, y + h);
		glVertex2i(x + w, y + h);
		glVertex2i(x + w, y);
	glEnd();
}

/*
bool Graphics::loadTexture(string fileName, SDL_Color *transparent)
{
	texture_.Free();

	bool result = true;
	SDL_Surface *surf = IMG_Load(fileName.c_str());

	if (!surf)
	{
		std::cerr << "[error] Unable to load image '" << fileName.c_str() << "'! IMG Error: " << IMG_GetError() << std::endl;
		result = false;
	}
	else
	{
		if (transparent)
			SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, transparent->r, transparent->g, transparent->b));

		texture_.sdlTexture_ = SDL_CreateTextureFromSurface(renderer_, surf);
		if (!texture_.sdlTexture_)
		{
			std::cerr << "[error] Unable to create texture from image '" << fileName.c_str() << "'! SDL Error: " << SDL_GetError() << std::endl;
			result = false;
		}
		else
		{
			//Get image dimensions
			texture_.width_ = surf->w;
			texture_.height_ = surf->h;
		}
		SDL_FreeSurface(surf);
	}

	return result;
}

void Graphics::addSprite(string name, int x, int y, int w, int h)
{
	Sprite sprite = { x, y, w, h };
	sprites_.insert(make_pair(name, sprite));
}

void Graphics::drawSprite(string name, int x, int y)
{
	Sprite s = sprites_[name];
	SDL_Rect rect = { x, y, s.w, s.h };
	SDL_RenderCopy(renderer_, texture_.sdlTexture_, &s, &rect);
}

void Graphics::drawSprite(string name, SDL_Rect rect)
{
	Sprite s = sprites_[name];
	SDL_RenderCopy(renderer_, texture_.sdlTexture_, &s, &rect);
}

void Graphics::drawSprite(string name, int x, int y, double angle)
{
	Sprite s = sprites_[name];
	SDL_Rect rect = { x, y, s.w, s.h };
	SDL_Point center = { s.w / 2, s.h / 2 }; 
	SDL_RenderCopyEx(renderer_, texture_.sdlTexture_, &s, &rect, angle, &center, SDL_FLIP_NONE);
}

void Graphics::drawSprite(string name, int x, int y, double angle, int centerX, int centerY)
{
	Sprite s = sprites_[name];
	SDL_Rect rect = { x, y, s.w, s.h };
	SDL_Point center = { centerX, centerY };
	SDL_RenderCopyEx(renderer_, texture_.sdlTexture_, &s, &rect, angle, &center, SDL_FLIP_NONE);
}

void Graphics::drawText(const Font &font, SDL_Color color, string text, int x, int y)
{
	//TODO: вывод русского текста
	SDL_Surface* surf = TTF_RenderUTF8_Blended(font.sdlFont_, text.c_str(), color);

	if (surf == NULL)
	{
		std::cerr << "[error] Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	else
	{
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer_, surf);
		if (tex == NULL)
		{
			std::cerr << "[error] Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			SDL_Rect rect = { x, y, surf->w, surf->h };
			SDL_RenderCopy(renderer_, tex, &surf->clip_rect, &rect);

			SDL_DestroyTexture(tex);
		}
		SDL_FreeSurface(surf);
	}
}

void Graphics::drawRect(SDL_Rect rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer_, &rect);
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
}
*/