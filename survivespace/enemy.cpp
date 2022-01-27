
#include "enemy.h"

Enemy::Enemy() : Collisionentity()
{
	this->addSprite("assets/enemy.tga");
	this->sprite()->size = Point2(100, 100);
	radius = 40;
}

Enemy::~Enemy()
{

}

void Enemy::update(float deltaTime)
{
	position += velocity * 500 * deltaTime;
}
