#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
private:
	float vel;
	int health;
	void (*TakeLife)(void);

public:
	Enemy(float x, float y, void (*TakeLife)(void), int vel);
	//Enemy(float x, float y);
	void Destroy();
	void Update(GameObject *otherObject);
	void Render();


	void Move(GameObject *otherObject);
	/*
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	*/

// maybe add this later	void SwitchGun(int gun) { player::gun = gun; }
//	int GetGun() { return gun; }
//	void Shoot();
	void LoseHealth(int damage) { health -= damage; }
	void Collided(GameObject *);
	int GetHealth() { return health; }
//	void AddPoint() { score++; }
//	void AddLife() { lives++; }
//	void StandingStill(int);
};

