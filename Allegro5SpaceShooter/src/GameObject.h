/*
 * GameObject.h
 *
 *  Created on: 02/04/2013
 *      Author: WiLL
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <allegro5/allegro.h>
#include "XY.h"


class GameObject {

	private:



protected:

	ALLEGRO_BITMAP *image;
	XY Position;
	XY Velocity;
	XY Direction;
	XY Bound;



public:
	GameObject();
	virtual ~GameObject();
};



#endif /* GAMEOBJECT_H_ */
