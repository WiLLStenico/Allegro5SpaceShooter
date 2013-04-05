/*
 * GameObject.cpp
 *
 *  Created on: 02/04/2013
 *      Author: WiLL
 */

#include "GameObject.h"

GameObject::GameObject(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity) {

	this->Image = image;
	this->ObjectDimention =objectDimention;
	this->Position = initialPosicion;
	this->Velocity = velocity;
}

GameObject::~GameObject() {
	al_destroy_bitmap(this->Image);


}

