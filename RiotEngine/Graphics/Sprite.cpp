#include "Sprite.h"
#include "../Graphics.h"
#include "Texture.h"

Sprite::Sprite(Texture &texture, int x, int y, int width, int height) :
	texture_(texture),
	x_(x),
	y_(y),
	width_(width),
	height_(height)
{
	setTexture(texture);
}

void Sprite::setTexture(Texture &t)
{
	texCoords_ = { 0, 0, 1, 1 };
}
