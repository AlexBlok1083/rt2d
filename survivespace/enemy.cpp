
#include "bullet.h"

Enemy::Enemy() : Entity()
{
	this->addSprite("assets/bullet.tga");
}

Enemy::~Enemy()
{

}

void Enemy::update(float deltaTime)
{
	position += velocity;
}
