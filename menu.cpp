#include "menu.h"


menu::menu(void)
{
	state = TOP;
	difficulty = EASY;
	font18 = al_load_font("arial.ttf", 18, 0);
}


menu::~menu(void)
{
}

void menu::RenderScreen(){
	//box surrounding the options with

	//render top menu
	switch(state){
	case TOP:
		break;
	case OPTIONS:
		break;
	case HELP:
		break;
	case DIFFICULTY:
		break;
	}
}

void menu::RenderTopMenu(){

	//play

	al_draw_text(font18, al_map_rgb(255, 255, 255), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "Start");

	//options

	al_draw_text(font18, al_map_rgb(255, 255, 255), SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 20, ALLEGRO_ALIGN_CENTRE, "Start");

	//help

	al_draw_text(font18, al_map_rgb(255, 255, 255), SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 40, ALLEGRO_ALIGN_CENTRE, "Start");

	//Exit

	al_draw_text(font18, al_map_rgb(255, 255, 255), SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 60, ALLEGRO_ALIGN_CENTRE, "Exit");
}


void menu::RenderOptionsMenu(){
	//difficulty
	al_draw_text(font18, al_map_rgb(255, 255, 255), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "Change Difficulty");
}


void menu::RenderHelpMenu(){
	//go through tutorials
}

void menu::RenderDifficultyMenu(){
	//Easy

	al_draw_text(font18, al_map_rgb(255, 255, 255), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "Easy");

	//medium

	al_draw_text(font18, al_map_rgb(255, 255, 255), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "Medium");

	//hard

	al_draw_text(font18, al_map_rgb(255, 255, 255), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "Hard");
}

int menu::SelectChoice(){
	return 0;
}