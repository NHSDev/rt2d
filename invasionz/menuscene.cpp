/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <time.h>

#include "menuscene.h"

MenuScene::MenuScene() : SceneManager()
{
	canvas = new Canvas(4);
}


MenuScene::~MenuScene()
{

}

void MenuScene::update(float deltaTime)
{
	// ###############################################################
	// Let manager do what it needs to do ( Escape key stops the Scene )
	// ###############################################################
	SceneManager::update(deltaTime);
}


