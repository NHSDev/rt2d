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

}


GameScene::~GameScene()
{

}

void GameScene::update(float deltaTime)
{
	// ###############################################################
	// Let manager do what it needs to do ( Escape key stops the Scene )
	// ###############################################################
	SceneManager::update(deltaTime);
	
}
