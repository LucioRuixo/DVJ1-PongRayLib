#ifndef PADDLES_H
#define PADDLES_H

#include "raylib.h"

struct Paddle
{
	Rectangle rec;
	Color color;

	int colorCode;
	int score;

	bool movement;
	bool up;
	bool right;
};

extern Paddle paddle1;
extern Paddle paddle2;

extern int IAPaddleSpeed;

extern bool paddle1LastToHit;

//----------------------------------------------------------------

Paddle InitPaddle();

#endif