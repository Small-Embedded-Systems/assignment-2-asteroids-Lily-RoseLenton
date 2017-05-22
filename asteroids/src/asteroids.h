/* Asteroids Game - Asteroids H File
	Lily-Rose Lenton & Alex Hutchinson
	CM0506
*/

/* Game state */

extern float 	elapsed_time; /* Time this ship has been active */

extern int 		score;				/* Total score held */
extern int 		lives;				/* Lives remaining */
extern int 		shield;				/* Hits that can be taken before death */

extern bool 	pause;				/* Stops play when true */

extern struct ship player; 	/* The players current ship, the position held */

extern const float Dt; 			/* Time step for physics, needed for consistent motion */

