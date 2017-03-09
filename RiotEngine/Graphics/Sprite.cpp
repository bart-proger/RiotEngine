#include "Sprite.h"
#include "../Graphics.h"
#include "Texture.h"
#include "../Math/Point2.h"


Sprite::Sprite():
	texture_(nullptr),
	texCoords_({ 0, 0, 1, 1 }),
	width_(0),
	height_(0),
	flippedH_(false),
	flippedV_(false),
	angle_(0),
	pivot_(0)
{
}

void Sprite::create(Texture &t)
{
	texture_ = &t;
	width_ = t.width();
	height_ = t.height();
	pivot_ = Point2{width_ / 2.f, height_ / 2.f};
}

void Sprite::create(Texture &t, int offsetX, int offsetY, int width, int height)
{
	texture_ = &t;
	width_ = width;
	height_ = height;
	pivot_ = width_ / 2.f, height_ / 2.f;

	float kx = 1.f / t.width();
	float ky = 1.f / t.height();
	texCoords_ = {offsetX * kx, offsetY * ky, (offsetX + width) * kx, (offsetY + height) * ky};
}

void Sprite::flip(FlipDir dir)
{
	if (dir == Horizontal || dir == All)
	{
		flippedH_ = !flippedH_;

		float tmp = texCoords_.u1;
		texCoords_.u1 = texCoords_.u2;
		texCoords_.u2 = tmp;
	}
	if (dir == Vertical || dir == All)
	{
		flippedV_ = !flippedV_;

		float tmp = texCoords_.v2;
		texCoords_.v2 = texCoords_.v1;
		texCoords_.v1 = tmp;
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