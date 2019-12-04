#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <rt2d/canvas.h>
#include "scenemanager.h"
#include "myentity.h"

class MenuScene : public SceneManager
{
public:

	MenuScene();

	virtual ~MenuScene();

	virtual void update(float deltaTime);

private:
	Canvas* canvas;
};

#endif /* MENUSCENE_H */
