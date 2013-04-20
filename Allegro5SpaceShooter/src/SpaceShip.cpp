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


		_currentFrame.X = _velocity.X<0?2:_velocity.X>0;
		_currentFrame.Y = 1 + 1*(_velocity.Y>0) + -1*(_velocity.Y<0);



		GameObject::Render();

	}



SpaceShip::~SpaceShip() {

}

} /* namespace std */
