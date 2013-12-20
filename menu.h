#pragma once
#include "Globals.h"
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>

class menu
{
private:
	int difficulty;
	int state;
	enum STATES{TOP, OPTIONS, HELP, DIFFICULTY};

	ALLEGRO_FONT *font18;
//	ALLEGRO_FONT *font18;
//	ALLEGRO_FONT *font18;
//	ALLEGRO_FONT *font18;
//	ALLEGRO_FONT *font18;
//	ALLEGRO_FONT *font18;


public:
	menu(void);
	~menu(void);

	int GetDifficulty() { return difficulty; }
	void SetDifficulty(int difficulty) { menu::difficulty = difficulty; }

	void RenderTopMenu();
	void RenderOptionsMenu();
	void RenderHelpMenu();
	void RenderDifficultyMenu();
	void RenderScreen();

	int SelectChoice();

};

