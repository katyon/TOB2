#pragma once
#include <math.h>

//#ifndef PI
//#define PI  3.14159265
//#endif

class Elastic {

public:

	// timer , total time (0), ( 1, -1 ), duration
	static float easeIn(float t, float b, float c, float d);
	static float easeOut(float t, float b, float c, float d);
	static float easeInOut(float t, float b, float c, float d);
};
