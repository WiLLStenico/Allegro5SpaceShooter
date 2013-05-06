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

	void CheckColision(list<Bullet *> object);
	bool isAlive() const;
	void setAlive(bool alive);
	const std::list<Bullet*>& getBullets() const;
	void setBullets(const std::list<Bullet*>& bullets);
	int getScore() const;
	void setScore(int score);

	Bullet *bullet; //TODO: remove from here

private:
	std::list<Bullet *> bullets;
	std::list<Bullet *>::iterator iter;

	int score;

	bool alive;

};


} /* namespace std */
#endif /* SPACESHIP_H_ */
