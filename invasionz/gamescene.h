#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>
#include <rt2d/timer.h>
#include <rt2d/vectorx.h>
#include <rt2d/canvas.h>
#include "scenemanager.h"

#define POINT_OF_NO_RETURN Pointi(-1000,-1000)

struct SI_AnimatedSprite {
	Pointi position;
	Pointi velocity;
	std::vector<PixelSprite> frames;
	void addPixelSprite(PixelSprite ps) {
		frames.push_back(ps);
	}
};

class GameScene : public SceneManager
{
public:
	GameScene();

	virtual ~GameScene();

	virtual void update(float deltaTime);

	

private:

	void restart();
	void setupTurret();
	void setupPlayer();
	void setupEnemyA();

	Canvas* canvas;
	PixelSprite player;
	PixelSprite turret;
	PixelSprite ground;
	SI_AnimatedSprite si_enemy_a;
};

#endif /* GAMESCENE_H */
