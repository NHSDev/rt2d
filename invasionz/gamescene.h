#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <rt2d/canvas.h>
#include "scenemanager.h"
#include "myentity.h"

class GameScene : public SceneManager
{
public:
	GameScene();

	virtual ~GameScene();

	virtual void update(float deltaTime);



private:
	Canvas* canvas;
};

#endif /* GAMESCENE_H */
