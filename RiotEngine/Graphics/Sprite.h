#pragma once

class Graphics;
class Texture;

class Sprite
{
	friend class Graphics;
public:
	struct TexCoords
	{
		float left, bottom, right, top;
	};

	Sprite(Texture &, int x, int y, int width, int height);
	void setTexture(Texture &);

//	void flipHorizontal();
//	void flipVertical();
//	void rotate(float angle);
//	void setRotation(float angle);

	float rotation() const { return angle_; }

private:
	Texture &texture_;
	TexCoords texCoords_;

	int x_, y_, width_, height_;
	bool flippedH_, flippedV_;
	float angle_;
};

