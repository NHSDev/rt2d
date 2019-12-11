/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <rt2d/scene.h>
#include "basicentity.h"

class SceneManager: public Scene
{
public:
	SceneManager();
	virtual ~SceneManager();

	virtual void update(float deltaTime);

	static int activescene;

protected:
	unsigned int top_layer;
	std::vector<BasicEntity*> layers;


private:
};

#endif /* SCENEMANAGER_H */
