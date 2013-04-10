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

	ALLEGRO_BITMAP *_image;

		XY _position;
		XY _velocity;
		Direction _direction;
		XY _bound;
		Dimension _objectDimention;
		XY _currentFrame;

protected:






public:

	GameObject(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity  );


	virtual ~GameObject();

	void Render();
	const XY& getBound() const;
	void setBound(const XY& bound);
	const XY& getCurrentFrame() const;
	void setCurrentFrame(const XY& currentFrame);
	const Direction& getDirection() const;
	void setDirection(const Direction& direction);
	const Dimension& getObjectDimention() const;
	void setObjectDimention(const Dimension& objectDimention);
	const XY& getPosition() const;
	void setPosition(const XY& position);
	const XY& getVelocity() const;
	void setVelocity(const XY& velocity);
};



#endif /* GAMEOBJECT_H_ */
