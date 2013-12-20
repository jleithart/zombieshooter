#pragma once

#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "Globals.h"


class GameObject
{
private:
	int ID; //player, wall, bullet, enemy, boss, gear
	bool alive;
	bool collidable;

protected:
	float x;
	float y;

	//angle the object is facing
	float angle;	//the direction the object is facing/heading

	int dirX;
	int dirY;

	float velX;	//max velocity the object can run E/W
	float velY;	//max velocity the object can run N/S

	int boundX;	//for collision
	int boundY; //for collision

	int damage;

public:
	GameObject();
	void virtual Destroy();

	void Init(float x, float y, float velX, float velY, int, int, float angle, int boundX, int boundY);
	void virtual Update(GameObject *otherObject);
	void virtual Render();

	float GetX() { return x; }
	float GetY() { return y; }

	float GetVelX() { return velX; }
	float GetVelY() { return velY; }

	float GetAngle() { return angle; }

	void SetX(float x) { GameObject::x = x;}
	void SetY(float y) { GameObject::y = y;}

	void SetVelX(float velX) { GameObject::velX = velX;}
	void SetVelY(float velY) { GameObject::velY = velY;}

	int GetBoundX() { return boundX; }
	int GetBoundY() { return boundY; }

	int GetID() { return ID; }
	void SetID(int ID) {GameObject::ID = ID;}

	bool GetAlive() { return alive; }
	void SetAlive(bool alive) {GameObject::alive = alive; }

	bool GetCollidable() { return collidable; }
	void SetCollidable(bool collidable) { GameObject::collidable = collidable; }

	bool CheckCollisions(GameObject *otherObject);
	void virtual Collided(GameObject *otherObject);
	bool Collidable();

	int GetDamage() { return damage; }
	void SetDamage(int damage) {GameObject::damage = damage; }


};

