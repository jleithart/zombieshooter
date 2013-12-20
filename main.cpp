/*
	Jordan Leithart Shooter
	Allegro Shell App

*/

// ALLEGRO INCLUDES
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <list>
#include <string>


//LOCAL INCLUES
#include "Globals.h"
#include "GameObject.h"
#include "player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Gear.h"
//#include "menu.h"

//local prototypes
double GetRadian(int xPos, int yPos, float mouseX, float mouseY);
void DrawReticle(int xPos, int yPos);
void DrawUI(ALLEGRO_FONT *);
void __cdecl TakeLife();
void __cdecl GetGear(int stuffID, int, int);
void ChangeState(int &, int);

//global variables
bool keys[] = {false, false, false, false};
bool guns[] = {false, false, false};
int difficulty[] = {3, 4, 5};
enum KEYS{W, A, S, D};
player *Player;

std::list<GameObject *> objects;
std::list<GameObject *>::iterator iter1;
std::list<GameObject *>::iterator iter2;


//main
int main(int argc, char *argv[]){

	bool done = false; //for the game loop
	bool render = false; //only draw every 60 seconds or so

	int frames = 0;
	float gameTime = 0;
	int gameFPS = 0;
	float pos_x = 0;
	float pos_y = 0;
	guns[PISTOL] = true;

	int state = -1;
	bool pause = false;


	Player = new player();
	Bullet *bullet;

	int level = 1;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font18;

	if(!al_init())
		return -1;

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

	if(!display)
		return -1;

	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	//Enemy *enemy = new Enemy(SCREEN_WIDTH/2 -200, SCREEN_HEIGHT/2-200, &TakeLife);
	//Enemy *enemy = new Enemy(SCREEN_WIDTH/2 -200, SCREEN_HEIGHT/2-200);

	font18 = al_load_font("arial.ttf", 18, 0);

	srand(time(NULL));

	Player->Init(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	objects.push_back(Player);

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0/60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();

	ChangeState(state, TITLE);
	
	al_hide_mouse_cursor(display);
	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_W:
				keys[W] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = true;
				break;
			case ALLEGRO_KEY_1:
				Player->SwitchGun(PISTOL);
				break;
			case ALLEGRO_KEY_2:
				if(guns[SHOTGUN])
					Player->SwitchGun(SHOTGUN);
				break;
			case ALLEGRO_KEY_3:
				if(guns[RIFLE])
					Player->SwitchGun(RIFLE);
				break;
			case ALLEGRO_KEY_SPACE:
				if(state == LOST){
					Player->SetAlive(true);
					guns[1] = false;
					guns[2] = false;
					Player->SetAmmo(SHOTGUN, 0);
					Player->SetAmmo(RIFLE, 0);
					Player->SetX(SCREEN_WIDTH/2);
					Player->SetY(SCREEN_HEIGHT/2);
					Player->SetHealth(10);
					ChangeState(state, PLAYING);
				}

			}
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			if(ev.mouse.button & 1){
				if(pause){
					pause = false;
				}
				else if(state == PLAYING){
					switch(Player->GetGun()){
					case PISTOL:
						//pistol!
						bullet = new Bullet(Player->GetX(), Player->GetY(), pos_x, pos_y, PISTOL);
						objects.push_back(bullet);
						break;
					case SHOTGUN:
						//SHOTGUN!!
						if(Player->GetAmmo(SHOTGUN) != 0){
							for(int i = 0; i < 3; i++){
								bullet = new Bullet(Player->GetX(), Player->GetY(), pos_x + i*5, pos_y - i*5, SHOTGUN);
								objects.push_back(bullet);
							}
							Player->Shoot(SHOTGUN);
						}
						break;
					case RIFLE:
						//rifle
						if(Player->GetAmmo(RIFLE) != 0){
							bullet = new Bullet(Player->GetX(), Player->GetY(), pos_x, pos_y, RIFLE);
							objects.push_back(bullet);
							Player->Shoot(RIFLE);
						}
						break;
					}
				}
				else if(state == TITLE){
					Player->SetAlive(true);
					guns[1] = false;
					guns[2] = false;
					Player->SetX(SCREEN_WIDTH/2);
					Player->SetY(SCREEN_HEIGHT/2);
					Player->SetHealth(10);
					ChangeState(state, PLAYING);
				}
			}
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY){
			pause = true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
			case ALLEGRO_KEY_W:
				keys[W] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = false;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER){
			render = true;

			frames++;
			if(al_current_time() - gameTime >= 1){
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

			//start pause
			if(!pause){

				//al_draw_filled_rectangle(0, 0, 50, 50, al_map_rgb(255, 0, 255));

				//start playing state
				if(state == PLAYING){
					if(keys[W]){
						//player move up
						Player->MoveUp();
					}
					else if(keys[S]){
						//player move down
						Player->MoveDown();
					}
					else{
						Player->StandingStill(0);
					}

					if(keys[A] && !keys[D]){
						//player move left
						Player->MoveLeft();
					}
					else if(keys[D] && !keys[A]){
						//player move right
						Player->MoveRight();
					}
					else{
						Player->StandingStill(1);
					}

					//bring on the zombies!!
					//Enemy *enemy = new Enemy(SCREEN_WIDTH/2 -200, SCREEN_HEIGHT/2-200, &TakeLife);a
					if(rand() % 40 == 0){
						int random = rand() % 4;
						int ex = 1;
						int ey = 1;
						if(random == 0){
							ex = SCREEN_WIDTH/2 + (SCREEN_WIDTH - LEVEL_LEFT_X);
							ey = rand() % SCREEN_HEIGHT/2;
						}
						else if(random == 1){
							ex = SCREEN_WIDTH/2 - (SCREEN_WIDTH - LEVEL_LEFT_X);
							ey = rand() % SCREEN_HEIGHT/2;
						}
						else if(random == 2){
							ex = rand() % SCREEN_WIDTH/2;
							ey = SCREEN_HEIGHT/2 + (SCREEN_HEIGHT - LEVEL_TOP_Y);;
						}
						else{
							ex = rand() % SCREEN_WIDTH/2;
							ey = SCREEN_HEIGHT/2 - (SCREEN_HEIGHT - LEVEL_TOP_Y);;
						}

						Enemy *enemy = new Enemy(ex, ey, &TakeLife, 3);
						objects.push_back(enemy);
					}

					//bring on the LOOOOOOT
					if(rand() % 500 == 0){
						int gearID = rand() % 3;
						//Gear *gear = new Gear(10, 10, 2, &GetGear(gearID));
						Gear *gear = new Gear(LEVEL_LEFT_X + (rand() % (LEVEL_RIGHT_X-LEVEL_LEFT_X-10)), 
												LEVEL_TOP_Y + (rand() % (LEVEL_BOT_Y - LEVEL_TOP_Y-10)), 
												gearID, &GetGear);
						objects.push_back(gear);
					}


					for(iter1 = objects.begin(); iter1 != objects.end(); ++iter1){
						if( (*iter1)->GetID() == PLAYER)
							Player->Update((*iter1));
						else if( (*iter1)->GetID() == ENEMY){
							(*iter1)->Update(Player);
						}
						else
							(*iter1)->Update((*iter1));
					}


					for(iter1 = objects.begin(); iter1 != objects.end(); ++iter1)
						{
							if( ! (*iter1)->Collidable() ) continue;

							for(iter2 = iter1; iter2 != objects.end(); ++iter2)
							{
								if( !(*iter2)->Collidable() ) continue;
								if( (*iter1)->GetID() == (*iter2)->GetID()) continue;

								if( (*iter1)->CheckCollisions( (*iter2)))
								{
									(*iter1)->Collided( (*iter2));
									(*iter2)->Collided( (*iter1));
								}
							}
						}
					// free up the memory being used by "dead" objects
					for(iter1 = objects.begin(); iter1 != objects.end(); ++iter1){
						if(!(*iter1)->GetAlive()){
							iter2 = iter1;
							(*iter2)->Destroy();
							delete (*iter2);
							(*iter2) = NULL;
						}
					}
				} //end playing state
			}//end pause

		}
		
		
		if(render && al_is_event_queue_empty(event_queue)){
			render = false;
			if(pause){
				al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "Click Left Mouse button to unpause!");
			}
			else if(state==TITLE){
				al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "Press left mouse button to play!");
			}
			else if(state==PLAYING){
				DrawReticle(pos_x, pos_y);

				for(iter1 = objects.begin(); iter1 != objects.end(); ++iter1){
					if( (*iter1)->GetID() == PLAYER){
						Player->Render(GetRadian(Player->GetX(), Player->GetY(), pos_x, pos_y));
					}
					else{
						(*iter1)->Render();
					}
				}

				//draw level border
			} //end playing state
			else if(state == LOST){
				al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "You lost!! Press Space button to play again, or press Esc to quit!");
			}
			DrawUI(font18);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
		if(Player->GetLives() <= 0){
			ChangeState(state, LOST);
			for(iter1 = objects.begin(); iter1 != objects.end(); ++iter1){
				(*iter1)->SetAlive(false);
				(*iter1)->Destroy();
			}

		}
	}//end while


}//end main

double GetRadian(int posX, int posY, float mouseX, float mouseY){
	double retval = 0;
	
	if(mouseX - posX >= 0){
		retval = atan((mouseY - posY)/(mouseX - posX));
	}
	else{
		retval = atan((mouseY - posY)/(mouseX - posX)) + M_PI;
	}

	return retval;

}

void DrawReticle(int pos_x, int pos_y){

	if(pos_x - 10 < LEVEL_LEFT_X)
		pos_x = LEVEL_LEFT_X + 10;
	if(pos_x + 11 > LEVEL_RIGHT_X)
		pos_x = LEVEL_RIGHT_X - 11;
	if(pos_y - 10 < LEVEL_TOP_Y)
		pos_y = LEVEL_TOP_Y + 10;
	if(pos_y + 11 > LEVEL_BOT_Y)
		pos_y = LEVEL_BOT_Y - 11;

	float range = 200;

	//draw it at the max range of the gun

	switch(Player->GetGun()){
	case PISTOL:
		range = 200;
		break;
	case SHOTGUN:
		range = 200;
		break;
	case RIFLE:
		range = 500;
		break;
	}
	float angle = GetRadian(Player->GetX(), Player->GetY(), pos_x, pos_y);
	if(sqrt( (Player->GetX() - pos_x)*(Player->GetX() - pos_x) + 
			 (Player->GetY() - pos_y)*(Player->GetY() - pos_y) ) > range){
		pos_x = Player->GetX() + (range*cos(angle));
		pos_y = Player->GetY() + (range*sin(angle));
	}
	

	al_draw_circle(pos_x, pos_y, 10, al_map_rgb(255, 0, 0), 1);
	al_draw_line(pos_x-13, pos_y, pos_x+13, pos_y, al_map_rgb(255, 0, 0), 2);
	al_draw_line(pos_x, pos_y-13, pos_x, pos_y+13, al_map_rgb(255, 0, 0), 2);
	al_draw_filled_circle(pos_x, pos_y, 3, al_map_rgb(0, 0, 0));
}

void __cdecl TakeLife(){
	Player->LoseLife();
}

void __cdecl GetGear(int stuffID, int gunID, int amount){
	ALLEGRO_FONT *font25;
	font25 = al_load_font("arial.ttf", 25, 0);
	std::string gun;
	switch(gunID){
	case SHOTGUN:
		gun = "Shotgun";
		break;
	case RIFLE:
		gun = "Rifle";
		break;
	}

	if(stuffID == AMMO || stuffID == GUN){
		Player->AddAmmo(gunID, amount);
		if(stuffID == GUN && !guns[gunID]){
			guns[gunID] = true;
		}			
	}
	else if(stuffID == HEALTH){
		for(int i = 0; i < amount; i++)
			Player->AddLife();
	}
}

void DrawUI(ALLEGRO_FONT *font18){

	al_draw_rectangle(LEVEL_LEFT_X, LEVEL_TOP_Y, LEVEL_RIGHT_X, LEVEL_BOT_Y, al_map_rgb(127, 127, 127), 10);

	std::string gun;
	ALLEGRO_COLOR pistol_color = al_map_rgb(120, 120, 120);
	ALLEGRO_COLOR shotgun_color = al_map_rgb(120, 120, 120);
	ALLEGRO_COLOR rifle_color = al_map_rgb(120, 120, 120);

	switch(Player->GetGun()){
	case PISTOL:
		gun = "Pistol";
		pistol_color = al_map_rgb(255, 255, 255);
		break;
	case SHOTGUN:
		gun = "Shotgun";
		shotgun_color = al_map_rgb(255, 255, 255);
		break;
	case RIFLE:
		gun = "Rifle";
		rifle_color = al_map_rgb(255, 255, 255);
		break;
	}
	
	al_draw_textf(font18, al_map_rgb(255, 0, 255), LEVEL_LEFT_X + 10, 25, 0, "Health: %d%%", Player->GetLives()*10);
	al_draw_filled_rectangle(SCREEN_WIDTH/2 - 175, LEVEL_BOT_Y + 15, SCREEN_WIDTH/2-75, LEVEL_BOT_Y + 35, pistol_color);
	al_draw_filled_rectangle(SCREEN_WIDTH/2 - 50, LEVEL_BOT_Y + 15, SCREEN_WIDTH/2 + 50, LEVEL_BOT_Y + 35, shotgun_color);
	al_draw_filled_rectangle(SCREEN_WIDTH/2 + 75, LEVEL_BOT_Y + 15, SCREEN_WIDTH/2+175, LEVEL_BOT_Y + 35, rifle_color);
	al_draw_textf(font18, al_map_rgb(255, 0, 255), LEVEL_LEFT_X + 10, LEVEL_BOT_Y + 15, 0, "Gun: %s", gun.c_str());
	if(Player->GetGun() == PISTOL){
		al_draw_textf(font18, al_map_rgb(255, 0, 255), LEVEL_RIGHT_X - 10, LEVEL_BOT_Y + 15, ALLEGRO_ALIGN_RIGHT, "Ammo: INF");
	}
	else
		al_draw_textf(font18, al_map_rgb(255, 0, 255), LEVEL_RIGHT_X - 10, LEVEL_BOT_Y + 15, ALLEGRO_ALIGN_RIGHT, "Ammo: %d", Player->GetAmmo(Player->GetGun())); 

	if(guns[PISTOL]){
		al_draw_line(SCREEN_WIDTH/2 - 140, LEVEL_BOT_Y + 21, SCREEN_WIDTH/2-110, LEVEL_BOT_Y+21, al_map_rgb(0, 0, 0), 5);
		al_draw_line(SCREEN_WIDTH/2 - 115, LEVEL_BOT_Y+21, SCREEN_WIDTH/2-110, LEVEL_BOT_Y+32, al_map_rgb(0, 0, 0), 10);
		al_draw_circle(SCREEN_WIDTH/2 - 120, LEVEL_BOT_Y+22, 4, al_map_rgb(0, 0, 0), 1);
	}

	if(guns[SHOTGUN]){
		al_draw_line(SCREEN_WIDTH/2 - 15, LEVEL_BOT_Y + 21, SCREEN_WIDTH/2+15, LEVEL_BOT_Y+21, al_map_rgb(0, 0, 0), 5);
		al_draw_line(SCREEN_WIDTH/2 + 10, LEVEL_BOT_Y+21, SCREEN_WIDTH/2 + 15, LEVEL_BOT_Y+32, al_map_rgb(0, 0, 0), 10);
		al_draw_circle(SCREEN_WIDTH/2 + 5, LEVEL_BOT_Y+22, 4, al_map_rgb(0, 0, 0), 1);
	}

	if(guns[RIFLE]){
		al_draw_line(SCREEN_WIDTH/2 + 110, LEVEL_BOT_Y + 21, SCREEN_WIDTH/2+140, LEVEL_BOT_Y+21, al_map_rgb(0, 0, 0), 5);
		al_draw_line(SCREEN_WIDTH/2 + 135, LEVEL_BOT_Y+21, SCREEN_WIDTH/2+140, LEVEL_BOT_Y+32, al_map_rgb(0, 0, 0), 10);
		al_draw_circle(SCREEN_WIDTH/2 +130, LEVEL_BOT_Y+22, 4, al_map_rgb(0, 0, 0), 1);
	}
}

void ChangeState(int &state, int NewState){
	state = NewState;
}