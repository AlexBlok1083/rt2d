
#ifndef MYENEMY_H
#define MYENEMY_H

#include <rt2d/entity.h>

/// @brief The MyEntity class is the Entity implementation.
class Enemy : public Entity
{
public:
	/// @brief Constructor
	Enemy();
	
	Vector2 velocity = Vector2(0, 0);
	/// @brief Destructor
	virtual ~Enemy();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	
	/* add your private declarations */
};

#endif /* MYENEMY_H */
