/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include "gamescene.h"


GameScene::GameScene() : SceneManager()
{
	timer.start();

	canvas = new Canvas(4); // pixelsize
	layers[0]->addChild(canvas);

	setupTurret();
	setupPlayer();
	setupEnemyA();

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
	// Let manager do what it needs to do ( Escape key stops the Scene )
	// ###############################################################
	SceneManager::update(deltaTime);

	updatePlayer();
}





void GameScene::restart() {
	canvas->fill(canvas->backgroundcolor);
	player.position.x = canvas->width() / 2;
}


void GameScene::updatePlayer() {
	canvas->clearSprite(player);
	if (input()->getKey(KeyCode::Left)) {
		float i = 0;
		i--;
		player = player.rotated(i);
	}
	if (input()->getKey(KeyCode::Right)) {
		float i = 0;
		i++;
		player = player.rotated(i);
	}
	canvas->drawSprite(player);
}






// ###############################################################
// Setup objects
// ###############################################################
void GameScene::setupTurret() {
	char turretsprite[338] = { // 26 * 13
		0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
		0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
		0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};

	turret.init(turretsprite, 26, 13);
	turret.position = Pointi(canvas->width() / 2, 8);
}


void GameScene::setupPlayer() {
	char playersprite[92] = { // 23 * 4
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0
	};

	player.init(playersprite, 23, 4);
	player.position = Pointi(canvas->width() / 2, 8);
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

