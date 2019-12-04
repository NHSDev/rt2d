/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "scenemanager.h"

int SceneManager::activescene = 0;

SceneManager::SceneManager() : Scene()
{

}


SceneManager::~SceneManager()
{

}

void SceneManager::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// ###############################################################
	// '[' and ']' switch scenes
	// ###############################################################
	if (input()->getKeyUp(KeyCode::LeftBracket)) {
		activescene--;
	}
	if (input()->getKeyUp(KeyCode::RightBracket)) {
		activescene++;
	}
}
