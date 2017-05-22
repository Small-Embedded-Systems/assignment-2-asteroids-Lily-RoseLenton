/* Asteroids Game - Utilities File
   Lily-Rose Lenton & Alex Hutchinson
   CM0506
*/
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "model.h"

/* some numerical helper functions */
float norm(float value, float min, float max) 
{
	return (value-min)/(max-min); 
}
float lerp(float min, float max, float value) 
{
	return max*value+(1.0f-value)*min; 
}
float map(float value, float lower, float upper, float min, float max) 
{
	return lerp(min,max, norm(value,lower,upper)); 
}
/*------*/

/* Produces a random number between values, not including the last randrange(from, to) */
int randrange(int from, int to)
{
	int range = to-from;
	return from + rand()%range;
}

/* Converts degrees to radians */
const float pi = 3.1415926f;
float radians(float degrees) { return degrees/180*pi; }
float degrees(float radians) { return radians * (180 / pi); }
