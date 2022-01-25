
#include "enemy.h"

Enemy::Enemy() : Entity()
{
	this->addSprite("assets/enemy.tga");
	this->scale = Point(3, 3);
}

Enemy::~Enemy()
{

}

void Enemy::update(float deltaTime)
{
	position += velocity * 500 * deltaTime;
}
