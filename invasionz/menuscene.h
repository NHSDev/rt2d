#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <rt2d/canvas.h>
#include "superscene.h"

struct AnimatedSprite {
	Pointi position;
	Pointi velocity;
	std::vector<PixelSprite> frames;
	void addPixelSprite(PixelSprite ps) {
		frames.push_back(ps);
	}
};

class MenuScene : public SuperScene
{
public:
	MenuScene();

	virtual ~MenuScene();

	virtual void update(float deltaTime);

private:
	Canvas* canvas;
	PixelSprite title;
	PixelSprite line;
	Timer timer;
	int i;
};

#endif /* MENUSCENE_H */
