// Tim Hagel
// C++ Programming (GAM327)
// Final Project:  Remake of Fast Food (Atari 2600)
// 04/27/09 - 05/01/09


#include <fastfood.h>
#include <stdio.h>


/////////////////////////////////////////////////////////////////////
// MAIN FUNCTION
/////////////////////////////////////////////////////////////////////

int main(void)
{

	printf("Initializing Fast Food...\n");
    //initialize the game
    allegro_init(); 
    install_keyboard(); 
    srand(time(NULL));
    setupscreen();
    setupmouth();
	setupfood();

    printf("Allegro Initialized...\n");
	buffer = create_bitmap(SCREEN_W, SCREEN_H);
 
    while(!gameover)
    {

  		blit(background,buffer,0,0,0,0,WIDTH,HEIGHT);
		
    	movemouth();
		drawmouth();
		updategpickle();
		updateppickle();
		updateburger();
		updatefries();
		updatedrink();
		updatepizza();
		updateicon();
		
		speedup();

        //check for keypresses
        if (keypressed())
            getinput();
  
		//Print Score....or don't really...
		textprintf_ex(buffer, font,(WIDTH/2-20),10,makecol(255,255,255),-1,
			"Score: %i", score);

  		blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);

		if (sickness >= 6)
		{
			restart();
		}

        //slow the game down
        rest(10);
    }
	

    //end program
    allegro_exit();
    return 0;
}
END_OF_MAIN()




/////////////////////////////////////////////////////////////////////
// DRAW mouth
/////////////////////////////////////////////////////////////////////

void drawmouth()
{
    int x = mouth.x - 15;
    int y = mouth.y - 15;
	//check mouth and load bitmap
	if (mouth.open == 0)
	{
		mouth_img = load_bitmap("../assets/mouth0.bmp",NULL);
		mouth.CO *= -1;
	}
	if (mouth.open == 10)
	{
		mouth_img = load_bitmap("../assets/mouth1.bmp",NULL);
		mouth.CO *= -1;
	}
    
	//draw the mouth
	draw_sprite(buffer, mouth_img, x, y);
	
	//change it for next time?
	mouth.open += mouth.CO; 


}


/////////////////////////////////////////////////////////////////////
// MOVE mouth
/////////////////////////////////////////////////////////////////////
void movemouth(){
    int spdx = mouth.speedx;
    int spdy = mouth.speedy;


    //keep mouth inside the screen
    //right
	if (mouth.x > SCREEN_W-50)
    {
        mouth.x = SCREEN_W-50;
        mouth.speedx = 0;
    }
	//left
    if (mouth.x < 20)
    {
        mouth.x = 20;
        mouth.speedx = 0;
    }
	//bottom
    if (mouth.y > SCREEN_H-50)
    {
        mouth.y = SCREEN_H-50;
        mouth.speedy = 0;
    }
	//top
    if (mouth.y < 20)
    {
        mouth.y = 20;
        mouth.speedy = 0;
    }

    mouth.x += spdx;
    mouth.y += spdy;

}


/////////////////////////////////////////////////////////////////////
// GET INPUT
/////////////////////////////////////////////////////////////////////
void getinput()
{
    //hit ESC to quit
    if (key[KEY_ESC])   gameover = 1;
    

    if (key[KEY_UP])    up();
    if (key[KEY_RIGHT]) right();
    if (key[KEY_DOWN])  down();
    if (key[KEY_LEFT])  left();

    //short delay after keypress        
    rest(20);
}

void up()
{
	if (mouth.speedy > 2)
		mouth.speedy = 2;
    mouth.speedy -= 2 ;
    if (mouth.speedy > MAXSPEEDY)
        mouth.speedy = MAXSPEEDY;
}

void down()
{	
	if (mouth.speedy < -2)
		mouth.speedy = -2;
    mouth.speedy += 2;
    if (mouth.speedy < -1*MAXSPEEDY)
        mouth.speedy = -1*MAXSPEEDY;
}

void left()
{
	if (mouth.speedx > 2)
		mouth.speedx = 2;
    mouth.speedx -= 2;
    if (mouth.speedx < -1*MAXSPEEDX)
        mouth.speedx = -1*MAXSPEEDX;
}

void right()
{
	if (mouth.speedx < -2)
		mouth.speedx = -2;
    mouth.speedx += 2;
    if (mouth.speedx > MAXSPEEDX)
        mouth.speedx = MAXSPEEDX;
}


/////////////////////////////////////////////////////////////////////
// UPDATE FOOD
/////////////////////////////////////////////////////////////////////
//GREEN PICKLE
void updategpickle()
{
	if (gpickle.lag > 10)
	{
		gpickle.lag = 0;
		gpickle.alive = 1;
		gpickle.x = 0;
		gpickle.y = (rand()%(HEIGHT-50)+25);
	}

	if (gpickle.alive == 1)
	{
		gpickle.x += gpickle.speed;
		draw_sprite(buffer, gpickle_img, gpickle.x, gpickle.y);
	}
	else
	{
		gpickle.lag++;
	}

	if (collided(mouth.x, mouth.y, gpickle.x, gpickle.y))
	{
		if (gpickle.alive==1)
			score += 20;
		gpickle.alive = 0;

	}

	if (gpickle.x > WIDTH)
		gpickle.alive = 0;
}
//PURPLE PICKLE
void updateppickle()
{
	if (ppickle.lag > 10)
	{
		ppickle.lag = 0;
		ppickle.alive = 1;
		ppickle.x = 0;
		ppickle.y = (rand()%(HEIGHT-50)+25);
	}

	if (ppickle.alive == 1)
	{
		ppickle.x += ppickle.speed;
		draw_sprite(buffer, ppickle_img, ppickle.x, ppickle.y);
	}
	else
	{
		ppickle.lag++;
	}

	if (collided(mouth.x, mouth.y, ppickle.x, ppickle.y))
	{
		if (ppickle.alive==1)
		{
			score -= 20;
			sickness++;
			ppicon[sickness].alive = 1;
		}
		ppickle.alive = 0;



	}

	if (ppickle.x > WIDTH)
		ppickle.alive = 0;
}
//BURGER
void updateburger()
{
	if (burger.lag > 200)
	{
		burger.lag = 0;
		burger.alive = 1;
		burger.x = 0;
		burger.y = (rand()%(HEIGHT-50)+25);
	}

	if (burger.alive == 1)
	{
		burger.x += burger.speed;
		draw_sprite(buffer, burger_img, burger.x, burger.y);
	}
	else
	{
		burger.lag++;
	}

	if (collided(mouth.x, mouth.y, burger.x, burger.y))
	{
		if (burger.alive==1)
			score += 200;
		burger.alive = 0;

	}

	if (burger.x > WIDTH)
		burger.alive = 0;
}
//FRIES
void updatefries()
{
	if (fries.lag > 50)
	{
		fries.lag = 0;
		fries.alive = 1;
		fries.x = 0;
		fries.y = (rand()%(HEIGHT-50)+25);
	}

	if (fries.alive == 1)
	{
		fries.x += fries.speed;
		draw_sprite(buffer, fries_img, fries.x, fries.y);
	}
	else
	{
		fries.lag++;
	}

	if (collided(mouth.x, mouth.y, fries.x, fries.y))
	{
		if (fries.alive==1)
			score += 40;
		fries.alive = 0;

	}

	if (fries.x > WIDTH)
		fries.alive = 0;
}
//DRINK
void updatedrink()
{
	if (drink.lag > 80)
	{
		drink.lag = 0;
		drink.alive = 1;
		drink.x = 0;
		drink.y = (rand()%(HEIGHT-50)+25);
	}

	if (drink.alive == 1)
	{
		drink.x += drink.speed;
		draw_sprite(buffer, drink_img, drink.x, drink.y);
	}
	else
	{
		drink.lag++;
	}

	if (collided(mouth.x, mouth.y, drink.x, drink.y))
	{
		if (drink.alive==1)
			score += 80;
		drink.alive = 0;

	}

	if (drink.x > WIDTH)
		drink.alive = 0;
}
//pizza
void updatepizza()
{
	if (pizza.lag > 150)
	{
		pizza.lag = 0;
		pizza.alive = 1;
		pizza.x = 0;
		pizza.y = (rand()%(HEIGHT-50)+25);
	}

	if (pizza.alive == 1)
	{
		pizza.x += pizza.speed;
		draw_sprite(buffer, pizza_img, pizza.x, pizza.y);
	}
	else
	{
		pizza.lag++;
	}

	if (collided(mouth.x, mouth.y, pizza.x, pizza.y))
	{
		if (pizza.alive==1)
			score += 150;
		pizza.alive = 0;

	}

	if (pizza.x > WIDTH)
		pizza.alive = 0;
}


/////////////////////////////////////////////////////////////////////
// UPDATE ICON FOR SICKNESS
/////////////////////////////////////////////////////////////////////

void updateicon()
{
	int n = 0;
	
	for (n=0; n<6; n++)
	{
		if (ppicon[n].alive == 1)
			draw_sprite(buffer, ppicon_img, (WIDTH-220+25*n), 10);
	}
}
			

/////////////////////////////////////////////////////////////////////
// SETUP AND LOAD mouth
/////////////////////////////////////////////////////////////////////
void setupmouth()
{
    
    //configure mouth
    mouth.x = WIDTH;
    mouth.y = HEIGHT;
    mouth.speedx = 0;
    mouth.speedx = 0;
	mouth.open = 1;
	mouth.CO = 1;

	mouth_img = load_bitmap("../assets/mouth0.bmp",NULL);
}


/////////////////////////////////////////////////////////////////////
// SETUP AND LOAD mouth
/////////////////////////////////////////////////////////////////////
void setupfood()
{
	gpickle_img = load_bitmap("../assets/gpickle.bmp",NULL);
	gpickle.alive = 0;
	gpickle.lag = 0;
	gpickle.speed = FOODSPEED;
	gpickle.x = 0;
	gpickle.y = 0;

	ppickle_img = load_bitmap("../assets/ppickle.bmp",NULL);
	ppickle.alive = 0;
	ppickle.lag = 0;
	ppickle.speed = FOODSPEED*2;
	ppickle.x = 0;
	ppickle.y = 0;

	burger_img = load_bitmap("../assets/burger.bmp",NULL);
	burger.alive = 0;
	burger.lag = 0;
	burger.speed = FOODSPEED*4;
	burger.x = 0;
	burger.y = 0;

	fries_img = load_bitmap("../assets/fries.bmp",NULL);
	fries.alive = 0;
	fries.lag = 0;
	fries.speed = FOODSPEED*2+2;
	fries.x = 0;
	fries.y = 0;

	drink_img = load_bitmap("../assets/drink.bmp",NULL);
	drink.alive = 0;
	drink.lag = 0;
	drink.speed = FOODSPEED*3;
	drink.x = 0;
	drink.y = 0;

	pizza_img = load_bitmap("../assets/pizza.bmp",NULL);
	pizza.alive = 0;
	pizza.lag = 0;
	pizza.speed = FOODSPEED*3+2;
	pizza.x = 0;
	pizza.y = 0;
}


/////////////////////////////////////////////////////////////////////
// SETUP AND LOAD SCREEN & SOUND
/////////////////////////////////////////////////////////////////////
void setupscreen()
{
    //set video mode    
	set_color_depth(32);
    int ret = set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);;

	if (ret != 0) {
        allegro_message(allegro_error);
        return;
    }

		background = load_bitmap("../assets/background.bmp",NULL);
		ppicon_img = load_bitmap("../assets/ppicon.bmp",NULL);

}



/////////////////////////////////////////////////////////////////////
// COLLISION DETECTION
/////////////////////////////////////////////////////////////////////

int inside(int x, int y, int left, int top, int right, int bottom)
{
	if (x > left && x < right && y > top && y < bottom)
		return 1;
	else
		return 0;
}

int collided(int mx, int my, int fx, int fy) //mouth and food
{

	int width1  = fx + 50;
	int height1 = fy + 50;
	int width2  = mx + 50;
	int height2 = my + 50;
	int middlex = fx + 25;
	int middley = fy + 25;
	
	//upper left
	if (inside (fx, fy, mx, my, width2, height2))
		return 1;
	//lower left
	if (inside (fx, height1, mx, my, width2, height2))
		return 1;
	//upper right
	if (inside (width1, fy, mx, my, width2, height2))
		return 1;
	//lower right
	if (inside (width1, height1, mx, my, width2, height2))
		return 1;
	//middle
	if (inside (middlex, middley, mx, my, width2, height2))
		return 1;

	//none?
	return 0;
}

/////////////////////////////////////////////////////////////////////
// SPEED UP THE GAME?
/////////////////////////////////////////////////////////////////////
void speedup()
{
	int n = 0;
	if (score >= levelup)
	{
		for (n=0; n < 100; n+=1)
		{
			blit(background,screen,0,0,0,0,WIDTH,HEIGHT);
			textprintf_ex(screen, font,(WIDTH/2-20),(HEIGHT/3+n),makecol(255,255,0),-1,
					"YOU'RE");
			textprintf_ex(screen, font,(WIDTH/2-20),(HEIGHT/3+20+n),makecol(255,255,0),-1,
					"GETTING");
			textprintf_ex(screen, font,(WIDTH/2-20),(HEIGHT/3+40+n),makecol(255,255,0),-1,
					"FATTER!");
		}

		levelup += 1000;
		ppickle.speed += 4;
		gpickle.speed += 4;
		burger.speed += 4;
		fries.speed += 4;
		drink.speed += 4;
		pizza.speed += 4;
		
		if (sickness > 0)
		{
			ppicon[sickness].alive = 0;
			sickness -=1;
		}
	}
}

/////////////////////////////////////////////////////////////////////
// RESTART THE GAME?
/////////////////////////////////////////////////////////////////////
void restart()
{
	int x = 0;
	int n = 0;
  	
	for (n=0; n < 60; n+=1)
	{
		blit(background,screen,0,0,0,0,WIDTH,HEIGHT);
		textprintf_ex(screen, font,(WIDTH/2-20),(HEIGHT/3+n),makecol(0,130,255),-1,
				"BURP!");
	}




	blit(background,screen,0,0,0,0,WIDTH,HEIGHT);

	while (x!=1)
	{
			textprintf_ex(buffer, font,(WIDTH/2-20),10,makecol(255,255,255),-1,
				"Score: %i", score);
			textprintf_ex(screen, font,(WIDTH/3-40),(HEIGHT/2-20),makecol(255,255,255),-1,
				"Would you like to try again?");
			textprintf_ex(screen, font,(WIDTH/3-40),(HEIGHT/2-60),makecol(255,255,255),-1,
				"Press SPACE to restart or ESC to quit.");

			if (key[KEY_SPACE])
			{
				gameover = 0;
				sickness = 0;
				score = 0;
				for (n=0; n<6; n++)
					ppicon[n].alive = 0;
				setupfood();
				x = 1;
			}

			if (key[KEY_ESC])
			{
				gameover = 1;
				x = 1;
			}

	}
	printf("gameover at start: %d\n", gameover);
}