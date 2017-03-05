#include "_Game.h"
/*#include "Graphics/Texture.h"*/

bool _Game::onInit()
{
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glBlendEquation(GL_FUNC_ADD);
	glEnable(GL_BLEND);

	if (!(tex.loadFromFile("data/ui.tga")))
		return false;
	else
		sprite = new Sprite(tex, 0, 272, 240, 240);

	if (!(t34_1.loadFromFile("data/t-34_1.tga")))
		return false;
	else
		t34_base = new Sprite(t34_1);
	if (!(t34_2.loadFromFile("data/t-34_2.tga")))
		return false;
	else
		t34_tower = new Sprite(t34_2);
	if (!(t44_1.loadFromFile("data/t-44_1.tga")))
		return false;
	else
		t44_base = new Sprite(t44_1);
	if (!(t44_2.loadFromFile("data/t-44_2.tga")))
		return false;
	else
		t44_tower = new Sprite(t44_2);
	
	//sprite->setPivot(Point2{50, 50});

	return true;
}

void _Game::onFree()
{
	delete sprite;
}

Uint32 ticks, start = SDL_GetTicks();
float dt = 0;

void _Game::onUpdate()
{
	ticks = SDL_GetTicks();
	dt = (ticks - start) / 1000.f;
	start = ticks;

	sprite->rotate(45 * dt);

	int mx, my;
	SDL_GetMouseState(&mx, &my);
	Point2 mouse{ mx * 1.f, my * 1.f };

	t34_tower->setRotation((mouse - Point2{ 20.f + t34_tower->width() / 2.f, 20.f + t34_base->height() / 2.f }).angle());
	t44_tower->setRotation((mouse - Point2{ 20.f + t44_tower->width() / 2.f, 300.f + t44_base->height() / 2.f }).angle());
}

void _Game::onDraw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	Graphics &g = graphics();

	//glColor3f(0, 1, 0);
	g.begin2D();
//		g.drawTexture(tex, 40, 100);
//		g.drawTexture(g.defaultTexture(), 0, 0, 200, 200);
		//g.drawSprite(*sprite, 200, 50);

		g.drawSprite(*t34_base, 20, 20);
		g.drawSprite(*t34_tower, 20, 20 + (t34_base->height() - t34_tower->height()) / 2);

		g.drawSprite(*t44_base, 20, 300);
		g.drawSprite(*t44_tower, 20, 300 + (t44_base->height() - t44_tower->height()) / 2);
	g.end2D();
}
