/*
 * SpaceShip.cpp
 *
 *  Created on: 11/04/2013
 *      Author: WiLL
 */

#include "SpaceShip.h"

namespace std {

SpaceShip::SpaceShip(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity):
  			GameObject(image, objectDimention, initialPosicion, velocity)
{

	//GameObject( *image,  objectDimention,  initialPosicion,  velocity  );

}

void SpaceShip::Render(){

	for(iter = bullets.begin(); iter != bullets.end(); ++iter){
					//bullet->Render();
					(*iter)->Render();
				}

	_currentFrame.X = _velocity.X<0?2:_velocity.X>0;
	_currentFrame.Y = 1 + 1*(_velocity.Y>0) + -1*(_velocity.Y<0);



	GameObject::Render();

}

void SpaceShip::Shoot(){
	bullet->setPosition({getPosition().X+5,
		getPosition().Y+(getObjectDimention().Height/2)-bullet->getObjectDimention().Height/2});

	bullet->setVelocity({getVelocity().X + 5,getVelocity().Y});
	bullets.push_back(new Bullet(*bullet));
}

SpaceShip::~SpaceShip() {

}

} /* namespace std */
