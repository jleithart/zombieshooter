#pragma once
#include "GameObject.h"

class Gear : public GameObject
{
private:

	int stuffID;
	int gunID;
	int amountGiven;
	void (*PickUpGear)(int, int, int);

public:
	Gear(float x, float y, int stuffID, void (*PickUpGear)(int, int, int));
	//Gear(float x, float y, int stuffID);
	void Destroy();
	void Update(GameObject *otherObject);
	void Render();
	void Collided(GameObject *);

	int GetAmount() { return amountGiven; }
	int GetStuffID() { return stuffID; }
	int GetGunID() { return gunID; }


};

