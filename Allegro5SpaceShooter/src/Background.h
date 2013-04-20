/*
 * Background.h
 *
 *  Created on: 14/04/2013
 *      Author: WiLL
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "GameObject.h"

namespace std {

class Background: public GameObject {
public:
  Background(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity );
	void Render();
	virtual ~Background();
};

} /* namespace std */
#endif /* BACKGROUND_H_ */
