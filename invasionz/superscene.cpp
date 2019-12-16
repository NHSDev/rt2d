/**
 * This class describes MyScene behavior.
 *
 * Copyright 2019 Nick Struik <Nick_Struik@outlook.com>
 */

#include "superscene.h"

int SuperScene::activescene = 0;

SuperScene::SuperScene() : Scene() {
	top_layer = 1; // 2 layers (0-1)

	for (unsigned int i = 0; i <= top_layer; i++) {
		BasicEntity* layer = new BasicEntity();
		layers.push_back(layer);
		this->addChild(layer);
	}

	for (unsigned int i = 0; i < 16; i++) {
		Text* line = new Text();
		line->scale = Point2(0.5f, 0.5f);
		text.push_back(line);
		layers[top_layer]->addChild(line);
	}
}

SuperScene::~SuperScene() {
	int ls = layers.size();
	for (int i = 0; i < ls; i++) {
		this->removeChild(layers[i]);
		delete layers[i];
		layers[i] = nullptr;
	}
	layers.clear();
}

void SuperScene::update(float deltaTime) {
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	unsigned int s = text.size();
	for (unsigned int i = 0; i < s; i++) {
		text[i]->position = Point2(SWIDTH / 3 + 50, SHEIGHT / 2 + 125);
	}

	// ###############################################################
	// switch scenes
	// ###############################################################
	if (activescene == 0 && input()->getKeyUp(KeyCode::Space)) {
		activescene++;
	}
}
