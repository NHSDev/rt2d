#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>
#include <rt2d/timer.h>
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
	float rotation = TWO_PI / 4;
	int bulletupdate = 4;
	int playerupdate = 1;
	int enemyupdate = 15;
	int enemytimer = 10;

	void setupTurret();
	void setupBullet();
	void setupEnemyA();
	void setupEnemyGrid();
	void setupExplosion();
	
	void restart();
	void updatePlayer(float deltaTime);
	void updateLaser();
	void updateEnemies();
	void updateBullets();

	std::vector<SI_AnimatedSprite> enemies;
	std::vector<PixelSprite> bullets;

	Canvas* canvas;
	Timer timer;
	Timer fpsTimer;
	Timer shootTimer;
	Timer laserTimer;

	PixelSprite barrel;
	PixelSprite turret;
	PixelSprite bullet;
	PixelSprite laser;
	PixelSprite ground;
	PixelSprite explosion;
	SI_AnimatedSprite si_enemy_a;

	Pointi enemycenter;
};

#endif /* GAMESCENE_H */
