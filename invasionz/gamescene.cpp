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
	canvas = new Canvas(4);
	restart();
}

GameScene::~GameScene()
{
	delete canvas;
}

void GameScene::update(float deltaTime)
{
	// ###############################################################
	// Let manager do what it needs to do ( Escape key stops the Scene )
	// ###############################################################
	SceneManager::update(deltaTime);
}

void GameScene::restart() {
	canvas->fill(canvas->backgroundcolor);
	layers[0]->addChild(canvas);
	player.position.x = canvas->width() / 2;


	setupEnemyA();
	
	canvas->drawSprite(player);
}

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
}


void GameScene::setupPlayer() {
	char playersprite[92] = { // 23 * 4
		0,1,1,0,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1
	};

	player.init(playersprite, 16, 8);
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

