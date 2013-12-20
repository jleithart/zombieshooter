#pragma once
#include "GameObject.h"
#include "Globals.h"

class Bullet : public GameObject
{
private:
	float range;
	int gun;
	float damage;
	float distanceTraveled;
	float vel;

public:
	//add void(*ScorePoint) later for score
	//void (*DamageEnemy)(int);
	Bullet(float x, float y, float mouseX, float mouseY, int gun);
	void Destroy();

	void Update(GameObject *otherObject);
	void Render();

	int GetGun() { return gun; }
	//void SetTravel(float dist) { distanceTraveled = dist; }

	void Collided(GameObject *);


};

