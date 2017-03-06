#pragma once
#include "RiotEngineApp.h"

#include "Graphics/Texture.h"
#include "Graphics/Sprite.h"

class _Game : public RiotEngineApp
{
public:
	_Game() {};
private:
	bool onInit() override;
	void onFree() override;
	void onUpdate() override;
	void onDraw() override;

	Texture tex, t34_1, t34_2, t44_1, t44_2;
	Sprite sprite, t34_base, t34_tower, t44_base, t44_tower;
};

