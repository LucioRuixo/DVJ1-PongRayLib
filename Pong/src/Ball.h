#ifndef BALL_H
#define BALL_H

#include "Game.h"

const int minBallSpeed = 15;
const int maxBallSpeed = 20;

struct Ball
{
	Vector2 position;
	Vector2 direction;
	Color color = RAYWHITE;

	int radius = 15;

	bool up;
	bool right;
};

Ball ball;

//----------------------------------------------------------------

void InitBall();

#endif