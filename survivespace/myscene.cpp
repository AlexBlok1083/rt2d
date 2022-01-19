/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"
#include "myentity.h"
#include "bullet.h"

MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();

	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	myentity = new MyEntity();
	myentity->position = Point2(SWIDTH/2, SHEIGHT/2);
	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(myentity);
}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(myentity);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete myentity;
}

void MyScene::updateBullets(float deltaTime)
{
	for (int i = bullets.size() - 1; i >= 0; i--) {
		if (bullets[i]->position.x > SWIDTH || bullets[i]->position.x < 0 || bullets[i]->position.y < 0 || bullets[i]->position.y > SHEIGHT) {
			removeChild(bullets[i]);
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
	}
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// ###############################################################
	// Spacebar scales myentity
	// ###############################################################
	if (input()->getKeyDown(KeyCode::Space)) {
		myentity->scale = Point(0.5f, 0.5f);
	}
	if (input()->getKeyUp(KeyCode::Space)) {
		myentity->scale = Point(1.0f, 1.0f);
	}

	// ###############################################################
	// Movement spaceship
	// ###############################################################
	float thrustspeed = 3;
	float bulletspeed = 5;
	
	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();

	Vector2 mousexy = Vector2(mousex, mousey);
	Vector2 cursorradius = Vector2(myentity->position, mousexy);
	Vector2 brake = Vector2(0, 0);

	float entityAngle = myentity->velocity.getAngle();

	if (input()->getKey(KeyCode::W)) {
		myentity->velocity += (mousexy - myentity->position) * thrustspeed * deltaTime; // thrust
	}	
	if (input()->getKey(KeyCode::S)) {
		myentity->velocity -= (mousexy - myentity->position) * (thrustspeed / 2) * deltaTime; // brake
	}
	if (input()->getMouseDown(0)) {
		std::cout << "Shoot" << std::endl;
		Vector2 bulletvel = (mousexy - myentity->position) * bulletspeed * deltaTime;
		bulletvel.normalize();
		Bullet* b = new Bullet();
		addChild(b);
		bullets.push_back(b);
		b->position = myentity->position;
		b->rotation = myentity->rotation;
		b->velocity = bulletvel;
	}

	updateBullets(deltaTime);
	myentity->rotation.z = cursorradius.getAngle() -  HALF_PI;
	myentity->position += myentity->velocity * deltaTime;

//	std::cout << myentity->velocity << std::endl;

	if (myentity->position.x < 0) { myentity->position.x = 0; }
	if (myentity->position.x > SWIDTH) { myentity->position.x = SWIDTH; }
	if (myentity->position.y < 0) { myentity->position.y = 0; }
	if (myentity->position.y > SHEIGHT) { myentity->position.y = SHEIGHT; }
}
