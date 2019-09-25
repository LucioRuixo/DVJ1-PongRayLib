#ifndef BALL_H
#define BALL_H

#include "raylib.h"

const int minBallSpeed = 15;
const int maxBallSpeed = 20;

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