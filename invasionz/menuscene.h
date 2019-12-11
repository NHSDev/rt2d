#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <rt2d/canvas.h>
#include "scenemanager.h"

struct AnimatedSprite {
	Pointi position;
	Pointi velocity;
	std::vector<PixelSprite> frames;
	void addPixelSprite(PixelSprite ps) {
		frames.push_back(ps);
	}
};

class MenuScene : public SceneManager
{
public:

	MenuScene();

	virtual ~MenuScene();

	virtual void update(float deltaTime);

private:
	void setupStart();
	void setupTitle();

	Canvas* canvas;
	PixelSprite title;
	AnimatedSprite start_a;
	AnimatedSprite start_b;
};

#endif /* MENUSCENE_H */
