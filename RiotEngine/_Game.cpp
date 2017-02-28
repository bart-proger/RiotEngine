#include "_Game.h"
#include <GL/GLU.h>

bool _Game::onInit()
{
	return true;
}

void _Game::onDraw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 1, 0);
	graphics().begin2D();
		graphics().drawRect(0, 0, 300, 300);
	graphics().end2D();
}
