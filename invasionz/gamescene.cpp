/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include "gamescene.h"

GameScene::GameScene() : SuperScene()
{
	timer.start();

	canvas = new Canvas(4); // pixelsize
	layers[0]->addChild(canvas);

	setupTurret();
	setupEnemyA();
	ground.position = Point2i(0, 0);

	restart();
	const unsigned int pixelsize = 8;
}

GameScene::~GameScene()
{
	layers[0]->removeChild(canvas);
	delete canvas;
}

void GameScene::update(float deltaTime)
{
	// ###############################################################
	// Let ss do what it needs to do ( Escape key stops the Scene )
	// ###############################################################
	SuperScene::update(deltaTime);

	static Vector2f vec = Vector2f(canvas->width() - 1, 0);
	canvas->clearSprite(ground);
	ground.pixels.clear(); // empty pixels array before creating new line
	ground.createLine(vec, WHITE); // vec, color
	canvas->drawSprite(ground);

	float tsec = timer.seconds();
	if (tsec > 0.05 - deltaTime) {
		static float a = TWO_PI / 4;
		
		static Vector2f vec = Vector2f(14, 0);
		canvas->clearSprite(barrel);
		barrel.pixels.clear(); // empty pixels array before creating new line
		barrel.createLine(vec, WHITE); // vec, color
		vec.rotation(a);

		if (a <= 2.8)
			if (input()->getKey(KeyCode::Left)) {
				a += PI / 60;
				if (a < 0) { a -= TWO_PI; }
				canvas->drawSprite(barrel);
			}

		if (a >= 0.35) {
			if (input()->getKey(KeyCode::Right)) {
				a -= PI / 60;
				if (a < 0) { a += TWO_PI; }
				canvas->drawSprite(barrel);
			}
		}
		canvas->drawSprite(barrel);
		canvas->drawSprite(turret);
		timer.start();
	}
}





void GameScene::restart() {
	canvas->fill(canvas->backgroundcolor);
	barrel.position.x = canvas->width() / 2;
	canvas->drawSprite(turret);
}


void GameScene::updatePlayer(float deltaTime) {
	
}






// ###############################################################
// Setup objects
// ###############################################################
void GameScene::setupTurret() {
	char turretsprite[225] = { // 15 * 15
		0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,0,0,1,1,1,1,1,0,0,0,0,0
	};

	turret.init(turretsprite, 15, 15);
	turret.position = Pointi(canvas->width() / 2, 0);
}


void GameScene::setupEnemyA() {
	char enemyA0sprite[143] = { // 11*13
		0,0,1,0,0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,1,0,0,0,
		0,0,1,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,0,1,1,0,
		0,1,0,0,4,0,4,0,0,1,0,
		0,1,0,0,0,0,0,0,0,1,0,
		0,1,0,1,0,1,0,1,0,1,0,
		0,1,1,0,1,0,1,0,1,1,0,
		0,0,1,1,1,1,1,1,1,0,0,
		0,1,0,1,0,0,0,1,0,1,0,
		1,0,0,1,0,0,0,1,0,0,1,
		1,0,0,1,0,0,0,1,0,0,1,
		0,1,0,0,1,0,1,0,0,1,0
	};

	PixelSprite enemyA0;
	enemyA0.init(enemyA0sprite, 11, 13);
	enemyA0.position = Pointi(canvas->width() / 2, canvas->height() / 2);

	char enemyA1sprite[143] = { // 11*13
		0,0,0,0,1,0,1,0,0,0,0,
		0,0,0,1,0,0,0,1,0,0,0,
		0,0,1,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,0,1,1,0,
		0,1,0,0,4,0,4,0,0,1,0,
		0,1,0,0,0,0,0,0,0,1,0,
		0,1,0,1,0,1,0,1,0,1,0,
		0,1,1,0,1,0,1,0,1,1,0,
		0,0,1,1,1,1,1,1,1,0,0,
		0,1,0,1,0,0,0,1,0,1,0,
		0,1,0,1,0,0,0,1,0,1,0,
		0,1,0,0,1,0,1,0,0,1,0,
		1,0,0,0,0,0,0,0,0,0,1
	};

	PixelSprite enemyA1;
	enemyA1.init(enemyA1sprite, 8, 8);
	enemyA1.position = Pointi(canvas->width() / 2, canvas->height() / 2);

	si_enemy_a.addPixelSprite(enemyA0);
	si_enemy_a.addPixelSprite(enemyA1);
}

