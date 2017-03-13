#pragma once
#include "RiotEngineApp.h"

#include "Graphics/Texture.h"
#include "Graphics/Sprite.h"
#include "Graphics/AnimatedSprite.h"

class _Game : public RiotEngineApp
{
public:
	_Game() {};
private:
	bool onInit() override;
	void onFree() override;
	void onUpdate(float dt) override;
	void onDraw(Graphics &) override;
	void onPress(Point2 p) override;
	void onMouseMove(Point2 p, Point2 dp) override;

	Texture tex, t34_1, t34_2, t44_1, t44_2;
	Sprite sprite, t34_base, t34_tower, t44_base, t44_tower;
	Texture sonic;
	AnimatedSprite sonic_walk, sonic_run, sonic_roll;

	Texture explo;
	AnimatedSprite explosion;
};

