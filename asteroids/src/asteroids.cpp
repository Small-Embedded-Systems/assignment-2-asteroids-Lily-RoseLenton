/* Asteroids Game - Main File
	Lily-Rose Lenton & Alex Hutchinson
	CM0506
*/

/* C include libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* Hardware platform libraries */
#include <display.h>
#include <mbed.h>

/* Main game elements */
#include "model.h"
#include "view.h"
#include "controller.h"

/* Game state */
float 	elapsed_time; 
int   	score = 0;
int   	lives = 5;
int 		shield = 3;
struct 	ship player;
bool 		pause = true;

/* Game speed */
float 	Dt = 0.01f;

/* Ticker objects to manage physics, graphics and input */
Ticker model, view, controller;

/* Local Method Declarations*/
static void death();

/* Button used to begin play from Pause state */
DigitalIn userbutton(P5_3,PullUp); 

/* Main Method */
int main()
{
	init_DBuffer();
    
	view.attach( draw, 0.025);
	model.attach( physics, Dt);
	controller.attach( controls, 0.025);
	
	/* Pause to start */
	while(userbutton.read()){
		pause=true;
	}		pause = false;
	
	/* Main Loop */
	while(true) {
		// The player has limited amount of sheild lives, once they are less than 1
		// the player will die
		if(shield < 1) {
			death();
		}
		
		// Once the player has ran out of lives, the game will reset once the player resumes game
		if(lives < 1) {
			lives = 5;
			score = 0;
			elapsed_time = 0;
		}
	}
}

/* Static void function that is called once the player has crashed the
		ship. It will pause the game, reset all shield life, and takes one life */
static void death() {
	lives --;
	
	while(userbutton.read()){
		pause = true;
	}
	shield = 3; 
	pause = false;
}
