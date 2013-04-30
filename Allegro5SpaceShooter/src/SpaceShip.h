/*
 * SpaceShip.h
 *
 *  Created on: 11/04/2013
 *      Author: WiLL
 */

#ifndef SPACESHIP_H_
#define SPACESHIP_H_

#include <list>

#include "GameObject.h"
#include "Bullet.h"

namespace std {

class SpaceShip: public GameObject {
public:
  SpaceShip(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity );
	virtual ~SpaceShip();

	void Render();

	void Shoot();

	Bullet *bullet; //TODO: remove from here

private:
	std::list<Bullet *> bullets;
	std::list<Bullet *>::iterator iter;

};


} /* namespace std */
#endif /* SPACESHIP_H_ */
