/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "myentity.h"

MyEntity::MyEntity() : Collisionentity()
{
	this->addSprite("assets/playertest.tga");
	radius = 5;
}

MyEntity::~MyEntity()
{

}

void MyEntity::update(float deltaTime)
{
	
}
