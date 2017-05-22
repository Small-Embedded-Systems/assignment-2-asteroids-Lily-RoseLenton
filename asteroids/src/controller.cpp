/* Asteroids Game - Controller
	Lily-Rose Lenton & Alex Hutchinson
	CM0506
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/* Hardware platform libraries */
#include <mbed.h>

/* Asteroids libraries */
#include "model.h"
#include "asteroids.h"

/* Joystick 5-way switch */
enum position {right, down, left, up, centre};
DigitalIn joystick[] = {P5_0, P5_1, P5_4, P5_2, P5_3};

// Boolean to check position (pressed)
static bool jsPrsd(position);

/* Main controller method */
void controls(void)
{
	// If the game is not on pause, joystick input sent
	if (!pause){
		// Once player presses left, ship will move accordingly
		if (jsPrsd(left)){
			player.heading -= 5;
		}
		// Once player presses right, ship will move accordingly
		else if (jsPrsd(right)){
			player.heading += 5;
		}
		// Once player presses up, ship moves upward
		else if (jsPrsd(up)){
			player.engines = 1;
		}
		// Once player presses up, ship will break
		else if (jsPrsd(down)){
			player.engines = -1;
		}
		// If player wishes to shoot, centre is pushed down and misiles will fire
		else if (jsPrsd(centre)){
			player.fire = true;
		}
		// Once the player is not using any control, the ship will stop moving and the engine will deactivate
		if (!jsPrsd(down) && !jsPrsd(up)){
			player.engines = 0;
		}
	}
}

/* Boolean method that will return value true is button selected has been pressed */
bool jsPrsd(position p){
	bool result = false;
	static uint32_t state;
	state = joystick[p].read();
  if (state == 0){
		result = true;
	}	return result;
}
