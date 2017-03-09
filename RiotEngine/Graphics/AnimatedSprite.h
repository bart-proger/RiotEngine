#pragma once
#include "Sprite.h"
#include <vector>

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite() : currentFrame_(0), interval_(0), looped_(false) {}

	void create(Texture &);
	void create(Texture &, int offsetX, int offsetY, int frameWidth, int frameHeight, int framesInWidth, int framesInHeight); //TODO: 

	void setFrame(int n);
	int frame() const { return currentFrame_; }
	void Anmate(float dt);

private:
	std::vector<TexCoords> frames_;
	float currentFrame_;
	float interval_;	// в секундах
	bool looped_;
};

