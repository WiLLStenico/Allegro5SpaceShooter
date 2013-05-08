/*
 * GameObject.cpp
 *
 *  Created on: 02/04/2013
 *      Author: WiLL
 */

#include "GameObject.h"


GameObject::GameObject(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity) {

	_image = image;
	_objectDimention =objectDimention;
	_position = initialPosicion;
	_velocity = velocity;
	_currentFrame.X = 0;
	_currentFrame.Y = 0;
	_direction = RIGHT;
}

const XY& GameObject::getBound() const {
	return _bound;
}

void GameObject::setBound(int x, int y) {
	_bound = {x,y};
}

const XY& GameObject::getCurrentFrame() const {
	return _currentFrame;
}

void GameObject::setCurrentFrame(int x, int y) {
	_currentFrame = {x,y};
}

const Direction& GameObject::getDirection() const {
	return _direction;
}

void GameObject::setDirection(const Direction& direction) {
	_direction = direction;
}

const Dimension& GameObject::getObjectDimention() const {
	return _objectDimention;
}

void GameObject::setObjectDimention(int dx, int dy) {
	_objectDimention = {dx,dy};
}

const XY& GameObject::getPosition() const {
	return _position;
}

void GameObject::setPosition(XY position) {
	_position = position;
}

const XY& GameObject::getVelocity() const {
	return _velocity;
}

void GameObject::setVelocity(XY velocity) {
	_velocity = velocity;
}

GameObject::~GameObject() {
	al_destroy_bitmap(this->_image);


}

void GameObject::Render(){

	_position.Y += _velocity.Y ;//* (_direction == UP ? -1 : 1);
	_position.X += _velocity.X ;//* (_direction == LEFT ? -1 : 1);

	//al_draw_bitmap_region( _image , _currentFrame.X * _objectDimention.Width, _currentFrame.Y * _objectDimention.Height, _objectDimention.Width, _objectDimention.Height, _position.X, _position.Y, _direction);
	al_draw_bitmap_region( _image , _currentFrame.X * _objectDimention.Width, _currentFrame.Y * _objectDimention.Height, _objectDimention.Width, _objectDimention.Height, _position.X, _position.Y, _direction);

}



