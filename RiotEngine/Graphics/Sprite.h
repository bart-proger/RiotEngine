#pragma once
#include "../Math/Point2.h"

class Graphics;
class Texture;

class Sprite
{
	friend class Graphics;
public:
	enum FlipDir { Horizontal, Vertical, All };

	struct TexCoords
	{
		float left, bottom, right, top;
	};

	Sprite(Texture &);
	Sprite(Texture &, int offsetX, int offsetY, int width, int height);

	void flip(FlipDir dir);
	bool flipped(FlipDir dir);
	void rotate(float angle);
	void setRotation(float angle);
	float rotation() const { return angle_; }
	int width() const { return width_; }
	int height() const { return height_; }

private:
	Texture &texture_;
	TexCoords texCoords_;

	int width_, height_;
	Point2 offset_;
	Point2 pivot_; //TODO: ось вращения и все что с ней связано

	bool flippedH_, flippedV_;
	float angle_;
};

