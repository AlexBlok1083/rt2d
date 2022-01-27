
#include "bullet.h"

Bullet::Bullet() : Collisionentity()
{
	this->addSprite("assets/bullet.tga");
	width = 5;
	height = 15;
}

Bullet::~Bullet()
{

}

void Bullet::update(float deltaTime)
{
	position += velocity;
}
