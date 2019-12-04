/**
 * Copyright 2019 Nick Struik <you@yourhost.com>
 *
 * @brief Description of My Awesome Game.
 *
 * @file main.cpp
 *
 * @mainpage Invasionz
 */
#include <rt2d/core.h>

#include "menuscene.h"
#include "gamescene.h"




int main( void )
{
	Core core;
	
	std::vector<SceneManager*> scenes;
	scenes.push_back(new MenuScene()); 
	scenes.push_back(new GameScene()); 
	int s = scenes.size();

	// start running with the first Scene
	SceneManager* scene = scenes[0];
	int scenecounter = 0;
	int running = 1;
	while (running) {
		scenecounter = scene->activescene;
		if (scenecounter > s - 1) { scenecounter = 0; scene->activescene = 0; }
		if (scenecounter < 0) { scenecounter = s - 1; scene->activescene = s - 1; }
		scene = scenes[scenecounter];
		core.run(scene); // update and render the current scene
		core.showFrameRate(5); // show framerate in output every n seconds
		if (!scene->isRunning()) { running = 0; } // check status of Scene every frame
	}

	// delete all scenes
	for (int i = 0; i < s; i++) {
		delete scenes[i];
		scenes[i] = nullptr;
	}
	scenes.clear();

	return 0;
}
