/* Asteroids Game - View File
   Lily-Rose Lenton & Alex Hutchinson
   CM0506
*/
/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* Hardware platform libraries */
#include <display.h>
#include <mbed.h>

/* Main game elements */
#include "asteroids.h"
#include "model.h"
#include "utils.h"

Display *graphics = Display::theDisplay();

const colour_t background = rgb(4,0,46); /* SPACE BLUE - EVERY GIRLS IDEA OF A PERFECT SPACEY COLOUR */ 

/*Declarations of local methods*/
static void drawStart();
static void drawResume();
static void drawGameOver();
static void drawBanner();
static void drawShip();
static void drawShield();
static void drawAsteroids(struct asteroid *a);
static void drawMissiles(struct missile *m);
static coordinate_t getPoint(coordinate_t origin, int basex, int basey, float heading);

/* Functions for double buffering */
void init_DBuffer(void)
{   /* Used to initialise the LCD driver to use second frame in buffer */
  uint16_t *bufferbase = graphics->getFb();
  uint16_t *nextbuffer = bufferbase+ (480*272);
  LPC_LCD->UPBASE = (uint32_t)nextbuffer;
}

void swap_DBuffer(void)
{   /* Used to swaps frames used by the LCD driver and the graphics object */
  uint16_t *buffer = graphics->getFb();
  graphics->setFb( (uint16_t*) LPC_LCD->UPBASE);
  LPC_LCD->UPBASE = (uint32_t)buffer;
}

/* Main Draw Method */
void draw(void){
  //Draws the background
	graphics->fillScreen(background);
	//If the game has not started, then draw the start screen
	if(pause && lives == 5){
		drawStart();
	}
	//If the player has died and has remaining lives, then draw the respawn screen
	else if(pause && lives < 5 && lives > 0){
		drawResume();
	}	
	//If the player is out of lives, then draw the game over screen
	else if(pause && lives < 1){
		drawGameOver();
	}	
	//If the game is in play, then draw the game elements
	else{
		drawAsteroids(asteroidCurrent);
		drawMissiles(missileCurrent);
		drawBanner();
		drawShip();
	}
	//Display the elements drawn on the LCD screen
  swap_DBuffer();
}

/* Draws the title screen complete with controls and credits */
static void drawStart(){
	graphics->setCursor(25, 50);
	graphics->setTextColor(WHITE);
	graphics->setTextSize(8);
	graphics->printf("ASTEROIDS");
	
	graphics->setTextSize(2);
	graphics->setCursor(33, 110);
	graphics->printf("Lily-Rose Lenton & Alex Hutchinson");
	
	graphics->setTextSize(2);
	graphics->setCursor(80, 170);
	graphics->printf("Press the joystick to start");
	graphics->setTextSize(1);
	graphics->setCursor(180, 180);

}

/* Draws the death screen */
static void drawResume(){
	graphics->setCursor(35, 40);
	graphics->setTextColor(WHITE); 
	graphics->setTextSize(5);
	graphics->printf("YOU'VE CRASHED");
	graphics->setCursor(70, 100);
	graphics->setTextSize(2);
	graphics->printf("Press joystick to continue...");
	graphics->setTextSize(3);
	graphics->setCursor(35,150);
	graphics->printf("Your current score is %d", score);
	graphics->setCursor(10,210);
	graphics->printf("You have %d lives remaining", lives);
}

/* Draws the game over screen*/
static void drawGameOver(){
	graphics->setCursor(80, 40);
	graphics->setTextColor(WHITE); 
	graphics->setTextSize(6);
	graphics->printf("GAME OVER");
	graphics->setCursor(60, 150);
	graphics->setTextSize(2);
	graphics->printf("Press the joystick to restart..."); 
	graphics->setTextSize(2);
	graphics->setCursor(145,200);
	graphics->printf("Final Score: %d", score);
}

/* Draws the banner information containing the players lives, score and shield status */
static void drawBanner(){
	graphics->setCursor(5,4);
	graphics->setTextSize(1);
	graphics->setTextColor(WHITE);
	graphics->printf("Lives: %d", lives);
	graphics->setCursor(180,4);
	graphics->drawRect(229, 2, 62, 10, WHITE);
	graphics->setCursor(400,4);
	graphics->printf("Score: %d", score);
}


/* Draws the players ship */
static void drawShip(){
	float heading = radians(player.heading);
	coordinate_t front, backR, backL;
	//Calculates the three points of the triangle based on the players heading
	front = getPoint(player.position, 0, -8, heading);
	backL = getPoint(player.position, 5, 5, heading);
	backR = getPoint(player.position, -5, 5, heading);
	graphics->drawTriangle(front.x, front.y, backL.x, backL.y, backR.x, backR.y, WHITE); 
	//Draw the ships Shields
	drawShield();
}

/* Draws the shield around the ship and the shield guide bar in the information banner */
static void drawShield(){
	//As the shield is damaged it turns red and the shield guide bar in the info banner reduces
	if (shield == 3){        
		graphics->drawCircle(player.position.x, player.position.y, 12, GREEN);   
		graphics->fillRect(230, 2, 60, 8, GREEN); 
	}
	else if (shield == 2){        
		graphics->drawCircle(player.position.x, player.position.y, 12, YELLOW);   
		graphics->fillRect(230, 2, 30, 8, YELLOW); 
	}
	else{
		graphics->drawCircle(player.position.x, player.position.y, 12, RED);
		graphics->fillRect(230, 2, 15, 8, RED); 
	}
}

/* Calculates a point based on its origin and displacement*/
static coordinate_t getPoint(coordinate_t origin, int basex, int basey, float heading){
	coordinate_t result;
	result.x = (basex * cos(heading)) - (basey * sin(heading));
	result.y = (basex * sin(heading)) + (basey * cos(heading));
	result.x += origin.x;
	result.y += origin.y;
	return result;
}

/* Iterates through the list of asteroids and draw each one if it is still alive */
void drawAsteroids(struct asteroid *a){
	while (a){
		if (a->live){
			graphics->drawCircle(a->position.x, a->position.y, a->size, rgb(51, 28, 12)); 
			graphics->fillCircle(a->position.x, a->position.y, a->size, rgb(92, 51, 23)); 
		}
		a = a->next;
	}
}

/* Iterates through the list of missiles and draw each one if it is still alive */
void drawMissiles(struct missile *m){
	while (m){
		if(m->live){
			graphics->fillCircle(m->position.x, m->position.y, 3, RED); 
		}
		m = m->next;
	}
}
