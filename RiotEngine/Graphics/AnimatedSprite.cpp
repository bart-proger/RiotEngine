#include "AnimatedSprite.h"


void AnimatedSprite::setFrame(int n)
{
	if (n < 0 || n >= frames_.size())
		return;

	currentFrame_ = n;
}

void AnimatedSprite::Anmate(float dt)
{
	currentFrame_ += (dt / interval_);
	int count = frames_.size();

	if (currentFrame_ > count - 1)
	{
		if (looped_)
			currentFrame_ = (int)currentFrame_ % count + (currentFrame_ - (int)currentFrame_);
		else
			currentFrame_ = count - 1;
	}
}
