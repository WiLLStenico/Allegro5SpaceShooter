/*
 * GameObject.cpp
 *
 *  Created on: 02/04/2013
 *      Author: WiLL
 */

#include "GameObject.h"

GameObject::GameObject(ALLEGRO_BITMAP *image, Dimension objectDimention, XY initialPosicion, XY velocity) {

	this->_image = image;
	this->_objectDimention =objectDimention;
	this->_position = initialPosicion;
	this->_velocity = velocity;
	_currentFrame.X = 0;
	_currentFrame.Y = 0;
}

const XY& GameObject::getBound() const {
	return _bound;
}

void GameObject::setBound(const XY& bound) {
	_bound = bound;
}

const XY& GameObject::getCurrentFrame() const {
	return _currentFrame;
}

void GameObject::setCurrentFrame(const XY& currentFrame) {
	_currentFrame = currentFrame;
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

void GameObject::setObjectDimention(const Dimension& objectDimention) {
	_objectDimention = objectDimention;
}

const XY& GameObject::getPosition() const {
	return _position;
}

void GameObject::setPosition(const XY& position) {
	_position = position;
}

const XY& GameObject::getVelocity() const {
	return _velocity;
}

void GameObject::setVelocity(const XY& velocity) {
	_velocity = velocity;
}

GameObject::~GameObject() {
	al_destroy_bitmap(this->_image);


}

void GameObject::Render(){

	_position.Y += _velocity.Y;
	_position.X += _velocity.X;

	//TODO: Colocar MOD da velocidade Ser 1,0,2
	//_currentFrame.X = _velocity.X  //abs(2* _direction[LEFT] -  _direction[RIGHT]);
	//_currentFrame.Y = 1  + _direction[DOWN] - _direction[UP];

	/*_position.Y -= _direction::UP * _velocity.Y;
	_position.Y += _direction::DOWN * _velocity.Y;
	_position.X -= _direction::LEFT * _velocity.X;
	_position.X += _direction::RIGHT * _velocity.X;*/

	//_currentFrame.X = abs(2* _direction[LEFT] -  _direction[RIGHT]);
	//_currentFrame.Y = 1  + _direction[DOWN] - _direction[UP];


	al_draw_bitmap_region( _image , _currentFrame.X * _objectDimention.Width, _currentFrame.Y * _objectDimention.Height, _objectDimention.Width, _objectDimention.Height, _position.X, _position.Y, 0);

}



