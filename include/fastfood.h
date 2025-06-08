#ifndef _SPACEINVADERS_H
#define _SPACEINVADERS_H

#include <allegro.h>

#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480
#define MAXSPEEDY 10
#define MAXSPEEDX 22
#define FOODSPEED 4

//define mouth structure
struct tagMouth
{
	int x, y;
	int speedx, speedy;
	int alive;
	int open;
	int CO;
} mouth;

//define food structure
struct tagFood
{
	int x, y;
	int alive;
	int lag;
	int speed;
} gpickle, ppickle, burger, fries, drink, pizza;

struct tagIcon
{
	int alive;
} ppicon[15];


int gameover = 0;
long score = 0;
int sickness = 0;
int levelup = 1000;


BITMAP *ppickle_img;
BITMAP *gpickle_img;
BITMAP *burger_img;
BITMAP *fries_img;
BITMAP *drink_img;
BITMAP *pizza_img;

BITMAP *mouth_img;
BITMAP *ppicon_img;
BITMAP *background;
BITMAP *buffer;



//function prototypes
void drawmouth();
void movemouth();
void up();

void down();
void left();
void right();
void getinput();

void updategpickle();
void updateppickle();
void updateburger();
void updatefries();
void updatedrink();
void updatepizza();

void updateicon();

void setupfood();
void setupmouth();
void setupscreen();
int inside(int x, int y, int left, int top, int right, int bottom);
int collided(int ex, int ey, int lx, int ly);
void speedup();
void restart();

#endif