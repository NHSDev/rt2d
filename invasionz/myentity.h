/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef MYENTITY_H
#define MYENTITY_H

#include <rt2d/entity.h>

class MyEntity : public Entity
{
public:
	MyEntity();

	virtual ~MyEntity();

	virtual void update(float deltaTime);

private:

};

#endif /* MYENTITY_H */
