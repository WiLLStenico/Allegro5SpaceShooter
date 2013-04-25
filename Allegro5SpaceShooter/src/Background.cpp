/*
 * Background.cpp
 *
 *  Created on: 14/04/2013
 *      Author: WiLL
 */

#include "Background.h"
#include <iostream>



namespace std {

Background::Background(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity, bool repeat, Dimension enviromentDimension):
  					GameObject(image, objectDimention, initialPosicion, velocity) {
	_repeat = repeat;
	_enviromentDimension = enviromentDimension;

}

void Background::Render(){

	if(!_repeat){
		GameObject::Render();
		return;
	}
	XY pos = _position;
	//GameObject::Render();

	//Repeat imageRender to draw the full screen
	for(; _position.Y  <= _enviromentDimension.Height; _position.Y +=_objectDimention.Height){
		for(_position.X = pos.X; _position.X  <= _enviromentDimension.Width; _position.X +=_objectDimention.Width ){

			GameObject::Render();
		}
	}

	_position = pos;
	_position.X -= _velocity.X;
}

Background::~Background() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
