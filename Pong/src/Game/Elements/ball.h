#ifndef BALL_H
#define BALL_H

#include "raylib.h"

const int ballSpeedIncrease = 25;
const int ballSpeedMin = 1200;

struct Ball
{
	Vector2 position;
	Vector2 direction;
	Color color;

	int radius;

	bool up;
	bool right;
};

extern Ball ball;

//----------------------------------------------------------------

void InitBall();

#endif