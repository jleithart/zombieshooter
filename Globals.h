#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int LEVEL_LEFT_X = 100;
const int LEVEL_RIGHT_X = SCREEN_WIDTH-100;
const int LEVEL_TOP_Y = 50;
const int LEVEL_BOT_Y = SCREEN_HEIGHT-50;

enum GUNS{PISTOL, SHOTGUN, RIFLE};
enum STATE{TITLE, PLAYING, LOST};
enum ID{PLAYER, BULLET, ENEMY, BOSS, WALL, GEAR};
enum STUFF{AMMO, HEALTH, GUN};	//add traps later
enum DIFFICULTY{EASY, MEDIUM, HARD};