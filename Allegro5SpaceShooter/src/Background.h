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


private:
	bool _repeat;
	Dimension _enviromentDimension;

public:
  Background(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity, bool repeat, Dimension enviromentDimension );
	void Render();
	virtual ~Background();
};

} /* namespace std */
#endif /* BACKGROUND_H_ */
