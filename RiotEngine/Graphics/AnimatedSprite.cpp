#include "AnimatedSprite.h"
#include "Texture.h"
//#include "../Graphics.h"


AnimatedSprite::AnimatedSprite():
	currentFrame_(0), 
	interval_(1.f / 15), 
	looped_(/*false*/true), 
	frameWidth_(0), 
	frameHeight_(0) 
{
}

void AnimatedSprite::create(Texture &t, int framesInWidth, int framesInHeight /*= 1*/)
{
	if (framesInWidth <= 0 || framesInHeight <= 0)
		return;

	Sprite::create(t);
	frameWidth_ = t.width() / framesInWidth;
	frameHeight_ = t.height() / framesInHeight;
	setPivot(Point2{frameWidth_ / 2.f, frameHeight_ / 2.f});

	frames_.clear();

	for (int row = 0; row < framesInHeight; ++row)
	{
		float y = 1.f * row * frameHeight_;
		for (int col = 0; col < framesInWidth; ++col)
		{
			float x = 1.f * col * frameWidth_;
			frames_.push_back(TexCoords{ x / t.width(), y / t.height(), (x + frameWidth_) / t.width(), (y + frameHeight_) / t.height() });
		}
	}
}

void AnimatedSprite::create(Texture &t, int offsetX, int offsetY, int width, int height, int framesInWidth, int framesInHeight /*= 1*/)
{
	if (framesInWidth <= 0 || framesInHeight <= 0)
		return;

	Sprite::create(t, offsetX, offsetY, width, height);
	frameWidth_ = width / framesInWidth;
	frameHeight_ = height / framesInHeight;
	setPivot(Point2{ frameWidth_ / 2.f, frameHeight_ / 2.f });

	frames_.clear();

	for (int row = 0; row < framesInHeight; ++row)
	{
		float y = 1.f * row * frameHeight_ + offsetY;
		for (int col = 0; col < framesInWidth; ++col)
		{
			float x = 1.f * col * frameWidth_ + offsetX;
			frames_.push_back(TexCoords{ x / t.width(), y / t.height(), (x + frameWidth_) / t.width(), (y + frameHeight_) / t.height() });
		}
	}
}


void AnimatedSprite::animate(float dt)
{
	if (currentFrame_ < 0)
		return;

	currentFrame_ += (dt / interval_);
	int count = frames_.size();

	if (currentFrame_ > count - 1)
	{
		if (looped_)
			currentFrame_ = (int)currentFrame_ % count + (currentFrame_ - (int)currentFrame_);
		else
			currentFrame_ = -1;
	}
}
