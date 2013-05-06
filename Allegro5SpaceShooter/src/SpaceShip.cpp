/*
 * SpaceShip.cpp
 *
 *  Created on: 11/04/2013
 *      Author: WiLL
 */

#include "SpaceShip.h"
#include <iostream>

namespace std {

SpaceShip::SpaceShip(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity):
  													GameObject(image, objectDimention, initialPosicion, velocity)
{

	setAlive(true);
	setScore(0);
	//GameObject( *image,  objectDimention,  initialPosicion,  velocity  );

}

void SpaceShip::Render(){

	for(iter = bullets.begin(); iter != bullets.end(); ++iter){
		//bullet->Render();
		(*iter)->Render();
		if(!(*iter)->isActive()){
			iter = bullets.erase(iter);
		}
	}


	if(!isAlive()) return;
	_currentFrame.X = _velocity.X<0?2:_velocity.X>0;
	_currentFrame.Y = 1 + 1*(_velocity.Y>0) + -1*(_velocity.Y<0);

	GameObject::Render();

}

void SpaceShip::CheckColision(list<Bullet *> objects){

	list<Bullet *>::iterator iter;

	XY myXY = this->getPosition();
	Dimension myBound = this->getObjectDimention();

	for(iter = objects.begin(); iter != objects.end(); ++iter){
		XY otherXY = (*iter)->getPosition();
		Dimension otherBound = (*iter)->getObjectDimention();
		if( myXY.X + myBound.Width > otherXY.X - otherBound.Width &&
				myXY.X - myBound.Width < otherXY.X + otherBound.Width &&
				myXY.Y + myBound.Height > otherXY.Y - otherBound.Height &&
				myXY.Y - myBound.Height < otherXY.Y + otherBound.Height){

			setAlive(false);
		}
	}

}

void SpaceShip::Shoot(){

	/*bullet->setPosition({getPosition().X+5,
		getPosition().Y+(getObjectDimention().Height/2)-bullet->getObjectDimention().Height/2});

	bullet->setVelocity({getVelocity().X + 5,getVelocity().Y});*/
	bullet->Shoot({getPosition().X+10,
		getPosition().Y+(getObjectDimention().Height/2)-bullet->getObjectDimention().Height/2},
			{(getVelocity().X >0 ? getVelocity().X:0) + 5,getVelocity().Y/2});

	bullets.push_back(new Bullet(*bullet));
}

SpaceShip::~SpaceShip() {

}

bool SpaceShip::isAlive() const {
	return alive;
}

void SpaceShip::setAlive(bool alive) {
	this->alive = alive;
}

const std::list<Bullet*>& SpaceShip::getBullets() const {
	return bullets;
}

void SpaceShip::setBullets(const std::list<Bullet*>& bullets) {
	this->bullets = bullets;
}

int SpaceShip::getScore() const {
	return score;
}

void SpaceShip::setScore(int score) {
	this->score = score;
}

} /* namespace std */
