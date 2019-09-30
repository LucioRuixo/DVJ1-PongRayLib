#ifndef BALL_H
#define BALL_H

#include "raylib.h"

const int minBallSpeed = 1150;
const int maxBallSpeed = 1400;

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

void InitBall(Ball &ball);

#endif