#include "Bullet.h"

Bullet::Bullet(float x, float y, float mouseX, float mouseY, int gun){
	float velX = 0;
	float velY = 0;
	float angle = 0;
	Bullet::distanceTraveled = 0;
	Bullet::gun = gun;
	SetID(BULLET);

	if(mouseX - x >= 0){
		angle = atan((mouseY - y)/(mouseX - x));
	}
	else{
		angle = atan((mouseY - y)/(mouseX - x)) + M_PI;
	}


	float distance = sqrt((x - mouseX)*(x - mouseX) + (y - mouseY)*(y - mouseY));
	switch(gun){
	case PISTOL:
		vel = 10;
		velX = vel*cos(angle);
		velY = vel*sin(angle);
		//how many pixels the bullet travels;
		range = 200;
		SetDamage(50);
		damage = 50;
		//maxBullets = 3;
		break;
	case SHOTGUN:
		vel = 10;
		velX = vel*cos(angle);
		velY = vel*sin(angle);
		//how many pixels the bullet travels;
		range = 100;
		SetDamage(50);
		damage = 50;
		//maxBullets = 1;
		break;
	case RIFLE:
		vel = 20;
		velX = vel*cos(angle);
		velY = vel*sin(angle);
		//how many pixels the bullet travels;
		range = 500;
		SetDamage(100);
		//maxBullets = 1;
		break;
	}
	//std::cout << "velY:: "<< velY << std::endl;
	GameObject::Init(x, y, velX, velY, 1, 1, 0, 0, 0);
}

void Bullet::Destroy(){

}

void Bullet::Update(GameObject *otherObject){
	if(GetAlive()){
		GameObject::Update(otherObject);


		//this needs to change depending on the gun
		distanceTraveled += vel;

		if(distanceTraveled > range)
			SetAlive(false);

		if(x < LEVEL_LEFT_X)
			SetAlive(false);
		else if(x > LEVEL_RIGHT_X)
			SetAlive(false);
		else if(y < LEVEL_TOP_Y)
			SetAlive(false);
		else if(y > LEVEL_BOT_Y)
			SetAlive(false);
	}
}

void Bullet::Render(){
	if(GetAlive()){
		switch(GetGun()){
		case PISTOL:
			al_draw_filled_circle(x, y, 2, al_map_rgb(255, 255, 255));
			break;
		case SHOTGUN:
			al_draw_filled_circle(x, y, 2, al_map_rgb(255, 255, 255));
			break;
		case RIFLE:
			al_draw_filled_circle(x, y, 2, al_map_rgb(255, 255, 255));
			break;
		}
	}
}

void Bullet::Collided(GameObject *otherObject){
	if(otherObject->GetID() == ENEMY){
		//switch(GetGun())
		//damage the enemy
		SetAlive(false);
	}
}