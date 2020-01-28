/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <time.h>
#include "gamescene.h"

GameScene::GameScene() : SuperScene()
{
	fpsTimer.start();
	shootTimer.start();

	canvas = new Canvas(4); // pixelsize
	layers[0]->addChild(canvas);

	setupTurret();
	setupEnemyA();
	ground.position = Point2i(0, 0);

	srand(time(NULL));

	restart();
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

	float tsec = timer.seconds();
	if (tsec > 0.01 - deltaTime) {
		static int counter = 0;
		

		// player bullets
		if (counter%bulletupdate / 4 == 0) {
			updateLaser();
		}

		if (input()->getKey(KeyCode::Space)) {
			if (shootTimer.seconds() > 0.5f) {
				canvas->drawSprite(laser);
				shootTimer.start();
				/*PixelSprite b = bullet; // copy sprites etc
				b.position = barrel.position;
				bullets.push_back(b);
				shootTimer.start();*/
			}
		}

		// player update
		if (counter%playerupdate / 20 == 0) {
			updatePlayer(deltaTime);
		}

		if (counter%enemyupdate == 0) {
			updateEnemies();
		}

		checkEnemiesForLaser();
		checkEnemiesForGround();
		counter++;
		timer.start();
	}

	if (tsec > 0.01) {
		startEnemySpawn();
	}

	if (needRestart == 1) {
		needRestart = 0;
		restart();
	}
}

void GameScene::restart() {
	canvas->fill(canvas->backgroundcolor);
	barrel.position.x = canvas->width() / 2;
	barrel.position.y = 1;

	static Vector2f vec = Vector2f(canvas->width() - 1, 0);
	canvas->clearSprite(ground);
	canvas->clearSprite(turret);
	canvas->clearSprite(barrel);
	barrel.pixels.clear();
	ground.pixels.clear(); // empty pixels array before creating new line
	ground.createLine(vec, WHITE); // vec, color

	canvas->drawSprite(ground);
	canvas->drawSprite(turret);
	canvas->drawSprite(barrel);
}

void GameScene::updatePlayer(float deltaTime) {
	static Vector2f vec = Vector2f(14, 0);
	canvas->clearSprite(barrel);
	barrel.pixels.clear(); // empty pixels array before creating new line
	barrel.createLine(vec, WHITE); // vec, color
	vec.rotation(rotation);

	if (rotation <= 2.8) {
		if (input()->getKey(KeyCode::Left)) {
			rotation += PI / 120;
			if (rotation < 0) { rotation -= TWO_PI; }
			canvas->drawSprite(barrel);
		}
	}

	if (rotation >= 0.35) {
		if (input()->getKey(KeyCode::Right)) {
			rotation -= PI / 120;
			if (rotation < 0) { rotation += TWO_PI; }
			canvas->drawSprite(barrel);
		}
	}
	canvas->drawSprite(barrel);
	canvas->drawSprite(turret);
}

void GameScene::updateLaser() 
{
	static int counting = 0;
	static Vector2f vec = Vector2f(160, 0);
	canvas->clearSprite(laser);
	laser.pixels.clear(); // empty pixels array before creating new line
	laser.createLine(vec, GREEN); // vec, color
	laser.position = barrel.position;
	vec.rotation(rotation);
}

void GameScene::updateEnemies()
{
	static Pointi velocity = Pointi(1, 0);
	static int counter = 0;

	std::vector<SI_AnimatedSprite>::iterator it = enemies.begin();
	while (it != enemies.end()) {
		int todelete = 0;

		canvas->clearSprite((*it).frames[0]);
		canvas->clearSprite((*it).frames[1]);
		(*it).position.y -= 1;
		(*it).frames[0].position = (*it).position;
		(*it).frames[1].position = (*it).position;

		// draw
		if (counter % 8 < 4) {
			//if (counter%2 == 0) {
			canvas->drawSprite((*it).frames[0]);
		}
		else {
			canvas->drawSprite((*it).frames[1]);
		}

		++it;
	}
	counter++;
}

void GameScene::checkEnemiesForLaser()
{
	std::vector<SI_AnimatedSprite>::iterator it = enemies.begin();
	while (it != enemies.end()) {
		int todelete = 0;

		// check if laser hits this enemy
		Pointi epos = (*it).position;
		Pointi lpos = laser.position;

		int left = epos.x - 7; // 8 or 11 wide
		int right = epos.x + 7;
		int top = epos.y + 6;
		int bottom = epos.y - 6;

		if (lpos.x > left && lpos.x < right && lpos.y < top && lpos.y > bottom) {
			explosion.position = epos;
		}

		// actually delete the enemy
		if (todelete == 1) {
			canvas->clearSprite((*it).frames[0]);
			canvas->clearSprite((*it).frames[1]);
			it = enemies.erase(it);
		}
		else {
			++it;
		}
	}
}

void GameScene::checkEnemiesForGround()
{
	std::vector<SI_AnimatedSprite>::iterator it = enemies.begin();
	while (it != enemies.end()) {	
		if((*it).position.y < 7) {
			needRestart = 1;
			++it;
		}
		else {
			++it;
		}
	}
}

// ###############################################################
// Setup objects
// ###############################################################
void GameScene::startEnemySpawn()
{
	int wave_size = 2;
	for (size_t i = 0; i < wave_size; i++)
	{		
			int height = canvas->height() + 20;
			int width = 10;
			width += (rand() % 300);
			SI_AnimatedSprite e;
			e = si_enemy;
			e.position = Pointi(width, height);
			enemies.push_back(e);
	}
}


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

void GameScene::setupExplosion() {
	char explosionsprite[144] = { // 12 * 12
		1,0,0,1,0,0,0,1,0,0,1,
		0,1,0,0,1,0,1,0,0,1,0,
		0,0,1,0,0,0,0,0,1,0,0,
		1,0,0,0,0,0,0,0,0,0,1,
		0,1,0,0,0,0,0,0,0,1,0,
		0,0,0,0,0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,0,0,1,0,
		1,0,0,0,0,0,0,0,0,0,1,
		0,0,1,0,0,0,0,0,1,0,0,
		0,1,0,0,0,0,0,0,0,1,0,
		1,0,0,0,0,0,0,0,0,0,1
	};
	
	PixelSprite explosion;
	explosion.init(explosionsprite, 12, 12);
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
		0,1,0,1,0,0,0,1,0,1,0,
		0,1,0,0,1,0,1,0,0,1,0,
		1,0,0,0,0,0,0,0,0,0,1
	};

	PixelSprite enemyA1;
	enemyA1.init(enemyA1sprite, 11, 13);
	enemyA1.position = Pointi(canvas->width() / 2, canvas->height() / 2);

	si_enemy.addPixelSprite(enemyA0);
	si_enemy.addPixelSprite(enemyA1);
}

