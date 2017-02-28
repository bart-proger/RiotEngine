#include "_Game.h"
/*#include "Graphics/Texture.h"*/

bool _Game::onInit()
{
	glEnable(GL_TEXTURE_2D);

	if (!(tex.loadFromFile("data/ui.tga")))
		return false;

	return true;
}

void _Game::onFree()
{
}

void _Game::onDraw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//glColor3f(0, 1, 0);
	graphics().begin2D();
		graphics().drawTexture(tex, 40, 100);
	graphics().end2D();
}
