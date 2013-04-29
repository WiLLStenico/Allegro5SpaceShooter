/*
 * Bullet.h
 *
 *  Created on: 24/04/2013
 *      Author: WiLL
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "GameObject.h"

namespace std {

class Bullet: public GameObject {
public:
	Bullet(ALLEGRO_BITMAP *image, Dimension objectDimention, Dimension limits,XY startPosition, XY velocity);
	void Render();
	void Shoot(XY startPosition, XY velocity);
	virtual ~Bullet();

private:
	bool onFire;
	Dimension _limits;
};


} /* namespace std */
#endif /* BULLET_H_ */
