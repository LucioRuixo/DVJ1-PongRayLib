#include "Paddles.h"

void InitPaddle(Paddle paddle)
{
	paddle.rec.width = paddleWidth;
	paddle.rec.height = paddleHeight;
	paddle1.rec.x = (float)(screenWidth / 20);
	paddle.rec.y = (float)(screenHeight / 2 - paddleHeight / 2);
	paddle.color = RAYWHITE;
	paddle.colorCode = 0;
	paddle.score = 0;

	paddle2.rec.width = paddleWidth;
	paddle2.rec.height = paddleHeight;
	paddle2.rec.x = (float)(screenWidth / 20 * 19 - paddleWidth);
	paddle2.rec.y = (float)(screenHeight / 2 - paddleHeight / 2);
}