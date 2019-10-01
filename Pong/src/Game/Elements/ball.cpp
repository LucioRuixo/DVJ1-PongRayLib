#include "ball.h"

#include "Game/game.h"
#include "Game/States/gameplay.h"

Ball ball;

//----------------------------------------------------------------

void InitBall()
{
	ball.position = { screenWidth / 2, screenHeight / 2 };
	ball.direction = { ballSpeedMin, ball.direction.y = 0 };
	ball.color = RAYWHITE;

	ball.radius = 15;

	GetRandomValue(0, 1) ? ball.up = true : ball.up = false;

	point % 2 == 0 ? ball.right = true : ball.right = false;
}