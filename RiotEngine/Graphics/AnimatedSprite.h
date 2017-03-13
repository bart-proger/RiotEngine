#pragma once
#include "Sprite.h"
#include <vector>

class Graphics;

class AnimatedSprite : public Sprite
{
friend class Graphics;
public:
	AnimatedSprite();

	void create(Texture &, int framesInWidth, int framesInHeight = 1);
	void create(Texture &, int offsetX, int offsetY, int width, int height, int framesInWidth, int framesInHeight = 1); 

	void animate(float dt);

	void setFrame(int n) { if (n < 0 || n >= frames_.size()) return; currentFrame_ = n; }
	int frame() const { return static_cast<int>(currentFrame_); }
	void setInterval(float seconds) { if (interval_ <= 0) return; interval_ = seconds; }
	float interval() const { return interval_; }
	void setLooped(bool value) { looped_ = value; }

	int frameWidth() const { return frameWidth_; }
	int frameHeight() const  { return frameHeight_; }

private:
	std::vector<TexCoords> frames_;
	float currentFrame_;
	float interval_;	// в секундах
	bool looped_;
	int frameWidth_, frameHeight_;
};

