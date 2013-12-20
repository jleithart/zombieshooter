#pragma once
#include "GameObject.h"

class player : public GameObject{
private:
	int lives;
	int score;
	int gun;
	int ammo[3];

public:
	player();
	void Destroy();

	void Init(float x, float y);
	void Update(GameObject *otherObject);
	void Render(float a);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void SwitchGun(int gun) { player::gun = gun; }
	int GetGun() { return gun; }
	int GetAmmo(int gunID) { return ammo[gunID]; }
	void SetAmmo(int gunID, int amount) { ammo[gunID] = amount; }
	void Shoot(int gunID) { int amount = ammo[gunID]; amount--; ammo[gunID] = amount;}
	void AddAmmo(int gunID, int amount);
	int GetLives() { return lives; }
	void LoseLife() { lives--; }
	void AddPoint() { score++; }
	void AddLife() { lives++; }
	void SetHealth(int lives) { player::lives = lives; }
	void StandingStill(int);
};

