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
	void onDraw() override;

	Texture tex;
	Sprite* sprite;
};

