#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>
#include <rt2d/timer.h>
#include <time.h>
#include <rt2d/vectorx.h>
#include <rt2d/canvas.h>
#include "superscene.h"

#define POINT_OF_NO_RETURN Pointi(-1000,-1000)

struct SI_AnimatedSprite {
	Pointi position;
	Pointi velocity;
	std::vector<PixelSprite> frames;
	void addPixelSprite(PixelSprite ps) {
		frames.push_back(ps);
	}
};

class GameScene : public SuperScene {
public:
	GameScene();

	virtual ~GameScene();

	virtual void update(float deltaTime);

	

private:

	void updatePlayer(float deltaTime);

	void restart();
	void setupTurret();
	void setupEnemyA();

	Canvas* canvas;
	Timer timer;
	PixelSprite barrel;
	PixelSprite turret;
	PixelSprite ground;
	SI_AnimatedSprite si_enemy_a;
};

#endif /* GAMESCENE_H */
