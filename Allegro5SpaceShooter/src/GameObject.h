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
#include "Dimension.h"

class GameObject {

private:



protected:






public:

	ALLEGRO_BITMAP *Image;

	XY Position;
	XY Velocity;
	XY Direction;
	XY Bound;
	Dimension ObjectDimention;
	XY CurrentFrame;

	GameObject(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity  );

	virtual ~GameObject();
};



#endif /* GAMEOBJECT_H_ */
