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
	Bullet(ALLEGRO_BITMAP *image, Dimension objectDimention, Dimension limits);
	void Render();
	void Shoot(XY startPosition, XY velocity);
	virtual ~Bullet();
	bool isActive() const;
	void setActive(bool active);

private:
	bool onFire;
	Dimension _limits;
	bool active;
};


} /* namespace std */
#endif /* BULLET_H_ */
