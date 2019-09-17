#ifndef PADDLES_H
#define PADDLES_H

#include "Game.h"

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

Paddle paddle1;
Paddle paddle2;

int IAPaddleSpeed = 5;
bool paddle1LTH = true; //LTH = Last To Hit

//----------------------------------------------------------------

void InitPaddle(Paddle paddle);

#endif