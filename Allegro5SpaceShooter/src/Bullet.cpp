/*
 * Bullet.cpp
 *
 *  Created on: 24/04/2013
 *      Author: WiLL
 */

#include "Bullet.h"

namespace std {

Bullet::Bullet(ALLEGRO_BITMAP *image, Dimension objectDimention, Dimension limits):
	  	GameObject(image, objectDimention, {50,50}, {0,0}){
	onFire = false;
	_limits = limits;
}

void Bullet::Shoot(XY startPosition, XY velocity){
	onFire = true;
	_position = startPosition;
	_velocity = velocity;
}

void Bullet::Render(){
	if((onFire) && (_position.X < _limits.Width) && (_position.Y < _limits.Height))
	GameObject::Render();
}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
