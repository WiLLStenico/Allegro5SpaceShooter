/*
 * Background.cpp
 *
 *  Created on: 14/04/2013
 *      Author: WiLL
 */

#include "Background.h"
#include <iostream>



namespace std {

Background::Background(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity):
  			GameObject(image, objectDimention, initialPosicion, velocity) {
	// TODO Auto-generated constructor stub

}

void Background::Render(){
	XY pos = _position;
	//GameObject::Render();



//TODO: Alterar o 960 para WIDTH
	for(; _position.X  <= 960; _position.X +=_objectDimention.Width ){
		GameObject::Render();
	}

	_position = pos;
	_position.X -= _velocity.X;
}

Background::~Background() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
