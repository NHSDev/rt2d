/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <time.h>

#include "menuscene.h"

MenuScene::MenuScene() : SuperScene() {
	canvas = new Canvas(4);
	layers[0]->addChild(canvas);
	timer.start();
	i = 0;
	line.position = Point2i(0,0);
}


MenuScene::~MenuScene() {
	layers[0]->removeChild(canvas);
	delete canvas;
}

void MenuScene::update(float deltaTime) {
	// ###############################################################
	// Let SS do what it needs to do ( Escape key stops the Scene )
	// ###############################################################
	SuperScene::update(deltaTime);

	static Vector2f vec = Vector2f(canvas->width() - 1, 0);
	canvas->clearSprite(line);
	line.pixels.clear(); // empty pixels array before creating new line
	line.createLine(vec, WHITE); // vec, color
	canvas->drawSprite(line);

	float tsec = timer.seconds();
	if (tsec > 0.5 - deltaTime) {
		if (i == 0) {
			text[0]->message("Press Space to start");
			i++;
		}
		else if (i == 1) {
			text[0]->clearMessage();
			i--;
		}
		timer.start();
	}
}




