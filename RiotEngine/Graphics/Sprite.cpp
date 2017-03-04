#include "Sprite.h"
#include "../Graphics.h"
#include "Texture.h"

Sprite::Sprite(Texture &t):
	texture_(t),
	offset_(0),
	width_(t.width()),
	height_(t.height()),
	angle_(0)
{
	texCoords_ = { 0, 0, 1, 1 };
}

Sprite::Sprite(Texture &t, int offsetX, int offsetY, int width, int height) :
	texture_(t),
	offset_(offsetX, offsetY),
	width_(width),
	height_(height),
	angle_(0)
{
	float kx = 1.f / t.width();
	float ky = 1.f / t.height();
	texCoords_ = { offsetX * kx, offsetY * ky, (offsetX + width) * kx, (offsetY + height) * ky};
}

void Sprite::flip(FlipDir dir)
{
	if (dir == Horizontal || dir == All)
	{
		flippedH_ = !flippedH_;

		float tmp = texCoords_.left;
		texCoords_.left = texCoords_.right;
		texCoords_.right = tmp;
	}
	if (dir == Vertical || dir == All)
	{
		flippedV_ = !flippedV_;

		float tmp = texCoords_.top;
		texCoords_.top = texCoords_.bottom;
		texCoords_.bottom = tmp;
	}
}

bool Sprite::flipped(FlipDir dir)
{
	if (dir == All)
		return flippedH_ && flippedV_;
	
	return (dir == Horizontal ? flippedH_ : flippedV_);
}

void Sprite::rotate(float angle)
{
	angle_ += angle;

	if (angle_ >= 360)
		angle_ -= 360;
	else if (angle_ < 0)
		angle_ += 360;
}

void Sprite::setRotation(float angle)
{
	angle_ = 0;
	rotate(angle);
}