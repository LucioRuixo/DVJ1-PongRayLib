#include "Paddles.h"

#include "Game.h"

Paddle paddle1;
Paddle paddle2;

int IAPaddleSpeed;

//----------------------------------------------------------------

Paddle InitPaddle()
{
	Paddle paddle;

	paddle.rec.width = paddleWidth;
	paddle.rec.height = paddleHeight;
	paddle.rec.y = (float)(screenHeight / 2 - paddleHeight / 2);
	paddle.color = RAYWHITE;
	paddle.colorCode = 0;
	paddle.score = 0;

	return paddle;
}