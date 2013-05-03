/*
 * BulletManager.h
 *
 *  Created on: 30/04/2013
 *      Author: WiLL
 */

#ifndef BULLETMANAGER_H_
#define BULLETMANAGER_H_

#include "Bullet.h"
#include <allegro5/allegro.h>

namespace std {

class BulletManager {
public:


	enum BulletType{
		NORMAL_RED,
		NORMAL_BLUE
	};


	Bullet* GetBullet(BulletType bulletType);
	BulletManager(Dimension limits);
	virtual ~BulletManager();
private:
	ALLEGRO_BITMAP *normalBulletImage;
	Dimension _limits;
};

} /* namespace std */
#endif /* BULLETMANAGER_H_ */
