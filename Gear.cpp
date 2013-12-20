#include "Gear.h"
#include <allegro5\allegro_font.h>


Gear::Gear(float x, float y, int stuffID, void (*PickUpGear)(int, int, int)){
	Gear::stuffID = stuffID;
	SetID(GEAR);
	SetAlive(true);
	
	switch(stuffID){
	case AMMO:
		gunID = rand() % 2 + 1 ;
		amountGiven = 20;
		break;
	case HEALTH:
		amountGiven = 4;
		break;
	case GUN:
		gunID = rand() % 2 + 1;
		amountGiven = 10;
		break;
	}

	Gear::PickUpGear = PickUpGear;

	GameObject::Init(x, y, 0, 0, 0, 0, 0, 14, 14);


}

void Gear::Destroy(){
	GameObject::Destroy();
}
void Gear::Update(GameObject *otherObject){
	GameObject::Update(otherObject);
}

void Gear::Render(){
	ALLEGRO_FONT *font12;
	al_init_font_addon();
//	al_init_ttf_addon();
	font12 = al_load_font("arial.ttf", 12, 0);

	if(GetAlive()){
		switch(GetStuffID()){
		case HEALTH:
			al_draw_filled_rectangle(x, y, x+boundX, y+boundY, al_map_rgb(255, 255, 255));
			al_draw_line(x + boundX/2, y + 2, x + boundX/2, y + boundY - 2, al_map_rgb(255, 0, 0), 3);
			al_draw_line(x + 2, y + boundY/2, x + boundX - 2, y + boundY/2, al_map_rgb(255, 0, 0), 3);
			break;
		case AMMO:
			//brown
			al_draw_filled_rectangle(x, y, x+boundX, y+boundY, al_map_rgb(0, 100, 0));
			al_draw_filled_rectangle(x+2, y+2, x+(boundX-2), y+boundY-2, al_map_rgb(205, 133, 63));
			//al_draw_text(font12, al_map_rgb(0, 0, 0), x+3, y+3, 0, "A");
			break;
		case GUN:
			//draw a gun?
			al_draw_filled_rectangle(x, y, x+boundX, y+boundY, al_map_rgb(0, 255, 0));
			al_draw_filled_rectangle(x+2, y+2, x+(boundX-2), y+boundY-2, al_map_rgb(0, 0, 255));
			//al_draw_text(font12, al_map_rgb(0, 0, 0), x+3, y+3, 0, "G");
			break;
		}
	}
}

void Gear::Collided(GameObject *otherObject){
	if(otherObject->GetID() == PLAYER){
		std::cout << GetGunID() << std::endl;
		PickUpGear(GetStuffID(), GetGunID(), GetAmount());
		SetAlive(false);
	}
}

