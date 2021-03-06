/*
 * BulletManager.cpp
 *
 *  Created on: 30/04/2013
 *      Author: WiLL
 */

#include "BulletManager.h"

namespace std {

BulletManager::BulletManager(Dimension limits) {

	normalBulletImage = al_load_bitmap("Resources//images//redBlueShoots.png");
	al_convert_mask_to_alpha(normalBulletImage, al_map_rgb(0, 0, 0));

	_limits = limits;

}

Bullet* BulletManager::GetBullet(BulletType bulletType){

	Bullet *bullet = NULL;
	bullet = new Bullet(normalBulletImage,{al_get_bitmap_width(normalBulletImage)/2,al_get_bitmap_height(normalBulletImage)},{_limits.Width,_limits.Height});

	switch(bulletType){
	case NORMAL_RED:
		bullet->setCurrentFrame(0,0);
		break;
	case NORMAL_BLUE:
		//the same of default
		bullet->setCurrentFrame(1,0);
		break;
	default:
		bullet->setCurrentFrame(1,0);
		break;
	}

	return bullet;

}

BulletManager::~BulletManager() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
