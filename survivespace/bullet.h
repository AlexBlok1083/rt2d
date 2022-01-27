
#ifndef MYBULLET_H
#define MYBULLET_H

#include <rt2d/entity.h>
#include "collisionentity.h"

/// @brief The MyEntity class is the Entity implementation.
class Bullet : public Collisionentity
{
public:
	/// @brief Constructor
	Bullet();
	
	Vector2 velocity = Vector2(0, 0);
	/// @brief Destructor
	virtual ~Bullet();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	
	/* add your private declarations */
};

#endif /* MYBULLET_H */