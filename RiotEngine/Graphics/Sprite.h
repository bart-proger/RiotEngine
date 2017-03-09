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
		float u1, v1, u2, v2;
	};

	Sprite();

	void create(Texture &);
	void create(Texture &, int offsetX, int offsetY, int width, int height);

	void flip(FlipDir dir);
	bool flipped(FlipDir dir);
	void rotate(float angle);
	void setRotation(float angle);
	float rotation() const { return angle_; }
	int width() const { return width_; }
	int height() const { return height_; }
	Point2 pivot() const { return pivot_; }
	void setPivot(Point2 value) { pivot_ = value; }

private:
	Texture *texture_;
	TexCoords texCoords_;

	int width_, height_;
	
	bool flippedH_, flippedV_;
	float angle_;
	Point2 pivot_;
};

