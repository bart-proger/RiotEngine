#pragma once
#include "RiotEngineApp.h"
#include "Graphics/Texture.h"

class _Game : public RiotEngineApp
{
public:
	_Game() {};
private:
	bool onInit() override;
	void onFree() override;
	void onDraw() override;

	Texture tex;
};

