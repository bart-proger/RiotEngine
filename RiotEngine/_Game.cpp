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
		sprite.create(tex, 0, 272, 240, 240);

	if (!(t34_1.loadFromFile("data/t-34_1.tga")))
		return false;
	else
		t34_base.create(t34_1);
	if (!(t34_2.loadFromFile("data/t-34_2.tga")))
		return false;
	else
		t34_tower.create(t34_2);
	if (!(t44_1.loadFromFile("data/t-44_1.tga")))
		return false;
	else
		t44_base.create(t44_1);
	if (!(t44_2.loadFromFile("data/t-44_2.tga")))
		return false;
	else
		t44_tower.create(t44_2);
	
	//sprite->setPivot(Point2{50, 50});

	sonic.loadFromFile("data/sonic.png");
	sonic_walk.create(sonic, 204, 0, 1024-204, 110, 10-2);
	sonic_run.create(sonic, 0, 116, 410, 110, 4);
	sonic_roll.create(sonic, 102, 240, 922-102, 82, 9-1);
	sonic_roll.setInterval(1.f / 40);

	explo.loadFromFile("data/explosion2.png");
	explosion.create(explo, 4, 4);
	explosion.setLooped(false);

	return true;
}

void _Game::onFree()
{
}

void _Game::onUpdate(float dt)
{
	sprite.rotate(45 * dt);

	int mx, my;
	SDL_GetMouseState(&mx, &my);
	Point2 mouse{ mx * 1.f, my * 1.f };

	t34_tower.setRotation((mouse - Point2{ 40.f + t34_tower.width() / 2.f, 20.f + t34_base.height() / 2.f }).angle());
	t44_tower.setRotation((mouse - Point2{ -20.f + t44_tower.width() / 2.f, 300.f + t44_base.height() / 2.f }).angle());

	sonic_walk.animate(dt);
	sonic_run.animate(dt);
	sonic_roll.animate(dt);

	explosion.animate(dt);
}

Point2 exploPos;

void _Game::onDraw(Graphics &g)
{
	glClear(GL_COLOR_BUFFER_BIT);

//	glColor3f(0, 1, 0);
	g.begin2D();
//		g.drawTexture(tex, 40, 100);
//		g.drawTexture(g.defaultTexture(), 0, 0, 200, 200);
		//g.drawSprite(*sprite, 200, 50);

		g.drawSprite(t34_base, 20, 20);
		g.drawSprite(t34_tower, 40, 20 + (t34_base.height() - t34_tower.height()) / 2);

		g.drawSprite(t44_base, 20, 300);
		g.drawSprite(t44_tower, -20, 300 + (t44_base.height() - t44_tower.height()) / 2);

		g.drawAnimatedSprite(sonic_walk, 300, 5);
		g.drawAnimatedSprite(sonic_run, 300, 150);
		g.drawAnimatedSprite(sonic_roll, 300, 300);

		g.drawAnimatedSprite(explosion, exploPos.x, exploPos.y);
	g.end2D();
}

void _Game::onPress(Point2 p)
{
	exploPos = p - Point2{explosion.frameWidth() / 2.f, explosion.frameHeight() / 2.f};
	explosion.setFrame(0);
}
