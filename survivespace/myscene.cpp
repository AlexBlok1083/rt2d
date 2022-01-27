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
#include "collision.h"

MyScene::MyScene() : Scene()
{
	// start the timer.
	spawntimer.start();
	timer.start();

	srand(time(nullptr));

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

void MyScene::updateEnemies(float deltaTime)
{
	for (int i = enemies.size() - 1; i >= 0; i--) {
		if (enemies[i]->position.x > SWIDTH || enemies[i]->position.x < 0 || enemies[i]->position.y < 0 || enemies[i]->position.y > SHEIGHT) {
			removeChild(enemies[i]);
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
	}
}

void MyScene::enemySpawn(float)
{
	Enemy* e = new Enemy();
	addChild(e);
	enemies.push_back(e);
	e->position.x = rand() % 1280;
	e->position.y = 0;
	Vector2 enemyvel = myentity->position - e->position;
	enemyvel.normalize();	
	e->velocity = enemyvel;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	//Speed aangeven.
	float thrustspeed = 3;
	float bulletspeed = 15;
	float enemyspeed = 2;

	//Muis locatiee op vragen.
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
		myentity->velocity -= (mousexy - myentity->position) * (thrustspeed / 2) * deltaTime; // brake/
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

	if (spawntimer.seconds() > enemyspawnrate) {
		enemySpawn(deltaTime);
		spawntimer.start();
	}

	if (timer.seconds() > 5 && enemyspawnrate > 0.25) {
		enemyspawnrate -= 0.25;
		timer.start();
		std::cout << enemyspawnrate << std::endl;
	}

	for (int i = 0; i < enemies.size(); i++) {
		if (Collision::circle2circle(myentity, enemies[i])) {
			this->stop();
		}
	}

	for (int i = enemies.size() - 1; i >= 0; i--) {
		for (int ii = 0; ii < bullets.size(); ii++) {
			if(Collision::circle2rectangle(enemies[i], bullets[ii])) {
				removeChild(enemies[i]);
				delete enemies[i];
				enemies.erase(enemies.begin() + i);

				std::cout << "Enemy geraakt door bullet" << std::endl;
				break;
			}
		}
	}
	//Het verwijderen van enetyties wanneer ze uit het scherm gaan.
	updateBullets(deltaTime);
	updateEnemies(deltaTime);

	myentity->rotation.z = cursorradius.getAngle() -  HALF_PI;
	myentity->position += myentity->velocity * deltaTime;
	
	//std::cout<< rand() % 1280 <<std::endl;
	
	// Boarders voor Player
	if (myentity->position.x < 0) { myentity->position.x = 0; }
	if (myentity->position.x > SWIDTH) { myentity->position.x = SWIDTH; }
	if (myentity->position.y < 0) { myentity->position.y = 0; }
	if (myentity->position.y > SHEIGHT) { myentity->position.y = SHEIGHT; }
}
