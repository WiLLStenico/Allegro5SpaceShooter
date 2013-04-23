/*
 * GameObject.h
 *
 *  Created on: 02/04/2013
 *      Author: WiLL
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "XY.h"
#include "Direction.h"

#include "Dimension.h"


class GameObject {

private:



protected:

	ALLEGRO_BITMAP *_image;

	XY _position;
	XY _velocity;
	Direction _direction;
	XY _bound;
	Dimension _objectDimention;
	XY _currentFrame;





public:

	GameObject(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity  );


	virtual ~GameObject();

	void Render();
	const XY& getBound() const;
	void setBound(int x, int y);
	const XY& getCurrentFrame() const;
	void setCurrentFrame(int x, int y);
	const Direction& getDirection() const;
	void setDirection(const Direction& direction);
	const Dimension& getObjectDimention() const;
	void setObjectDimention(int dx, int dy);
	const XY& getPosition() const;
	void setPosition(int x, int y);
	const XY& getVelocity() const;
	void setVelocity(int x, int y);
};



#endif /* GAMEOBJECT_H_ */
