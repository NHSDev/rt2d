/**
 * This class describes MyScene behavior.
 *
 * Copyright 2019 Nick Struik <Nick_Struik@outlook.com>
 */

#include "scenemanager.h"

int SceneManager::activescene = 0;

SceneManager::SceneManager() : Scene() {
	top_layer = 1; // 2 layers (0-1)

	for (unsigned int i = 0; i <= top_layer; i++) {
		BasicEntity* layer = new BasicEntity();
		layers.push_back(layer);
		this->addChild(layer);
	}
}


SceneManager::~SceneManager() {
	int ls = layers.size();
	for (int i = 0; i < ls; i++) {
		this->removeChild(layers[i]);
		delete layers[i];
		layers[i] = nullptr;
	}
	layers.clear();
}

void SceneManager::update(float deltaTime) {
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// ###############################################################
	// '[' and ']' switch scenes
	// ###############################################################
	if (activescene == 0 && input()->getKeyUp(KeyCode::Space)) {
		activescene++;
	}
}
