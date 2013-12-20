#include "Enemy.h"


Enemy::Enemy(float x, float y, void(*TakeLife)(void), int vel)
//Enemy::Enemy(float x, float y)
{
	SetID(ENEMY);
	SetAlive(true);
	health = 100;
	Enemy::vel = rand() % vel + 0.5;

	GameObject::Init(x, y, 0, 0, 1, 1, 0, 15, 15);

	Enemy::TakeLife = TakeLife;
}


void Enemy::Destroy(){
	GameObject::Destroy();
}

void Enemy::Update(GameObject *otherObject){
	Move(otherObject);
	GameObject::Update(otherObject);
}


void Enemy::Render(){
	if(GetAlive()){
		//only draw it if it's in the screen
		if(x > LEVEL_LEFT_X + 8 && x < LEVEL_RIGHT_X - 8 && y > LEVEL_TOP_Y - 8 && y < LEVEL_BOT_Y + 8)
			al_draw_filled_rectangle(x, y, x+boundX, y+boundY, al_map_rgb(107, 142, 35));
	}
}


void Enemy::Move(GameObject *otherObject){
	float dir;
	if(GetAlive()){
		if(otherObject->GetID() == PLAYER){
			if(otherObject->GetX() - x >= 0){
				dir = atan((otherObject->GetY() - y)/(otherObject->GetX() - x));
			}
			else{
				dir = atan((otherObject->GetY() - y)/(otherObject->GetX() - x)) + M_PI;
			}

			SetVelX(vel*cos(dir));
			SetVelY(vel*sin(dir));
		}
	}
}

void Enemy::Collided(GameObject *otherObject)
{
	if(otherObject->GetID() == PLAYER)
	{
		TakeLife();
		SetAlive(false);
	}

	if(otherObject->GetID() == BULLET){
		LoseHealth(otherObject->GetDamage());
		if(GetHealth() <= 0)
			SetAlive(false);
	}

}