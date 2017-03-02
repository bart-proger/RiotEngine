#include "_Game.h"
/*#include "Graphics/Texture.h"*/

bool _Game::onInit()
{
	glEnable(GL_TEXTURE_2D);

	if (!(tex.loadFromFile("data/ui.tga")))
		return false;

	sprite = new Sprite(tex, 0, 0, 200, 200);

	return true;
}

void _Game::onFree()
{
	delete sprite;
}

void _Game::onDraw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	Graphics &g = graphics();

	//glColor3f(0, 1, 0);
	g.begin2D();
		g.drawTexture(tex, 40, 100);
		g.drawTexture(g.defaultTexture(), 0, 0, 200, 200);
		g.drawSprite(sprite, 200, 50);
	g.end2D();
}
