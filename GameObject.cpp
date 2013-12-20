#include "GameObject.h"


GameObject::GameObject(void)
{
	x = 0;
	y = 0;

	velX = 0;
	velY = 0;
	angle = 0;

	dirX = 0;
	dirY = 0;

	boundX = 0;
	boundY = 0;
	
	alive = true;
	collidable = true;
}


void GameObject::Destroy(){
	
}

void GameObject::Init(float x, float y, float velX, float velY, int dirX, int dirY, float angle, int boundX, int boundY){
	GameObject::x = x;
	GameObject::y = y;

	GameObject::velY = velY;
	GameObject::velX = velX;
	GameObject::angle = angle;

	GameObject::dirX = dirX;
	GameObject::dirY = dirY;

	GameObject::boundX = boundX;
	GameObject::boundY = boundY;
}

void GameObject::Update(GameObject *otherObject){
	//change where they're looking

	//determine where they should be after one frame...
	x += velX * dirX;
	y += velY * dirY;
}

void GameObject::Render(){

}

bool GameObject::CheckCollisions(GameObject *otherObject){
	float oX = otherObject->GetX();
	float oY = otherObject->GetY();

	int obX = otherObject->GetBoundX();
	int obY = otherObject->GetBoundY();

	if( x + boundX > oX &&
		x - boundX < oX + obX &&
		y + boundY > oY &&
		//y < oY + obY){
		y - boundY < oY + obY){
		return true;
	}
	else
		return false;
}

void GameObject::Collided(GameObject *otherObject){}

bool GameObject::Collidable(){
	return alive && collidable;
}
