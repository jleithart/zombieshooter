#include "player.h"


player::player(void)
{
}


void player::Destroy()
{
}

void player::Init(float x, float y){
	GameObject::Init(x, y, 2, 2, 0, 0, 0, 7, 7);

	SetID(PLAYER);
	SetAlive(true);

	lives = 10;
	score = 0;
	gun = PISTOL;
	ammo[PISTOL] = -1;
	ammo[SHOTGUN] = 0;
	ammo[RIFLE] = 0;
}

void player::Update(GameObject *otherObject){
	GameObject::Update(otherObject);

	if(x - 10 < LEVEL_LEFT_X)
		x = LEVEL_LEFT_X + 10;
	if(x + 11 > LEVEL_RIGHT_X)
		x = LEVEL_RIGHT_X - 11;
	if(y - 10 < LEVEL_TOP_Y)
		y = LEVEL_TOP_Y + 10;
	if(y + 11 > LEVEL_BOT_Y)
		y = LEVEL_BOT_Y - 11;
}

void player::Render(float a){
	GameObject::Render();

	float fx = GetX();
	float fy = GetY();
	float obX = GetBoundX();
	float obY = GetBoundY();

	//al_draw_filled_rectangle(0, 0, 50, 50, al_map_rgb(255, 0, 255));
	//draw a line
	al_draw_line(fx, fy, fx + (cos(a))*(14), fy + (sin(a)) * (14), al_map_rgb(0, 255, 0), 2);
	al_draw_filled_circle(fx, fy, 7, al_map_rgb(0, 0, 255));
}

void player::MoveUp(){
	dirY = -1;
}

void player::MoveDown(){
	dirY = 1;
}
void player::MoveLeft(){
	dirX = -1;
}
void player::MoveRight(){
	dirX = 1;
}

void player::StandingStill(int direction){

	if(direction){
		dirX = 0;
	}
	else{
		dirY = 0;
	}
}

void player::AddAmmo(int gunID, int amount){
	if(gunID == PISTOL){
		ammo[gunID] = -1;
	}
	else{
		int newAmount = ammo[gunID];
		newAmount += amount;
		ammo[gunID] = newAmount;
	}
}
