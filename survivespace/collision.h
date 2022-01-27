
#ifndef COLLISION_H
#define COLLISION_H

#include <algorithm>
#include "collisionentity.h"

class Collision
{
public:
	
	/*static bool circle2circle(const Circle& circle1, const Circle& circle2) {
		float dx = circle1.x - circle2.x;
		float dy = circle1.y - circle2.y;
		float radii = circle1.radius + circle2.radius;
		return (dx * dx + dy * dy) < (radii * radii);
	}

	static bool circle2rectangle(const Circle& circle, const Rectangle& rect) {
		float mx = std::max(rect.x, std::min(circle.x, rect.x + rect.width));
		float my = std::max(rect.y, std::min(circle.y, rect.y + rect.height));
		float dx = circle.x - mx;
		float dy = circle.y - my;
		return (dx * dx + dy * dy) < (circle.radius * circle.radius);
	}*/
	static bool circle2circle(const Collisionentity* circle1, const Collisionentity* circle2) {
		float dx = circle1->position.x - circle2->position.x;
		float dy = circle1->position.y - circle2->position.y;
		float radii = circle1->radius + circle2->radius;
		return (dx * dx + dy * dy) < (radii * radii);
	}

	static bool circle2rectangle(const Collisionentity* circle, const Collisionentity* rect) {
		float mx = std::max(rect->position.x, std::min(circle->position.x, rect->position.x + rect->width));
		float my = std::max(rect->position.y, std::min(circle->position.y, rect->position.y + rect->height));
		float dx = circle->position.x - mx;
		float dy = circle->position.y - my;
		return (dx * dx + dy * dy) < (circle->radius * circle->radius);
	}

private:
	
	Collision() {}
};

#endif /* MYBULLET_H */
