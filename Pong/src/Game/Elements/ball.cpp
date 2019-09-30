#include "ball.h"

#include "Game/game.h"
#include "Game/States/gameplay.h"

Ball ball;

//----------------------------------------------------------------

void InitBall(Ball &ball)
{
	ball.position = { screenWidth / 2, screenHeight / 2 };
	ball.direction.x = static_cast<float>(GetRandomValue((minBallSpeed), (maxBallSpeed - 1))); ball.direction.y = maxBallSpeed - ball.direction.x;
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