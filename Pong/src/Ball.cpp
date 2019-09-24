#include "Game.h"
#include "Ball.h"

Ball ball;

//----------------------------------------------------------------

void InitBall()
{
	ball.position = { (float)screenWidth / 2, (float)screenHeight / 2 };
	ball.direction.x = (float)GetRandomValue(minBallSpeed, maxBallSpeed - 1); ball.direction.y = (float)(maxBallSpeed - ball.direction.x);
	ball.color = RAYWHITE;

	ball.radius = 15;

	randomN = GetRandomValue(1, 2);
	if (randomN == 1)
		ball.up = true;
	else
		ball.up = false;

	if (point % 2 == 0)
		ball.right = true;
	else
		ball.right = false;
}