#include "paddles.h"

#include "Game/game.h"

Paddle paddle1;
Paddle paddle2;

bool paddle1;

//----------------------------------------------------------------

Paddle InitPaddle()
{
	Paddle paddle;

	paddle.color = RAYWHITE;

	paddle.powerUp.timer = 0;
	paddle.powerUp.timerGoal = static_cast<float>(GetRandomValue(spawnTimerMin, spawnTimerMax));
	paddle.powerUp.active = false;

	paddle.rec.width = paddleWidth;
	paddle.rec.height = paddleHeight;
	paddle.rec.y = screenHeight / 2 - paddleHeight / 2;

	paddle.colorCode = 0;
	paddle.score = 0;

	return paddle;
}

void InitArrows(Paddle &paddle)
{
	paddle.leftArrow.v1 = { paddle.rec.x - 20, paddle.rec.y + paddleHeight / 2 - 20 };
	paddle.leftArrow.v2 = { paddle.rec.x - 40, paddle.rec.y + paddleHeight / 2 };
	paddle.leftArrow.v3 = { paddle.rec.x - 20, paddle.rec.y + paddleHeight / 2 + 20 };

	paddle.rightArrow.v1 = { paddle.rec.x + paddleWidth + 40, paddle.rec.y + paddleHeight / 2 };
	paddle.rightArrow.v2 = { paddle.rec.x + paddleWidth + 20, paddle.rec.y + paddleHeight / 2 - 20 };
	paddle.rightArrow.v3 = { paddle.rec.x + paddleWidth + 20, paddle.rec.y + paddleHeight / 2 + 20 };
}

void GeneratePaddleArrows(Paddle &paddle)
{
	DrawTriangle(paddle.leftArrow.v1, paddle.leftArrow.v2, paddle.leftArrow.v3, RAYWHITE);
	DrawTriangle(paddle.rightArrow.v1, paddle.rightArrow.v2, paddle.rightArrow.v3, RAYWHITE);

	if (((cursor.x > paddle.leftArrow.v2.x && cursor.x < paddle.leftArrow.v1.x)
		&&
		(cursor.y > paddle.leftArrow.v1.y && cursor.y < paddle.leftArrow.v3.y)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (paddle.colorCode > 0)
			paddle.colorCode--;
		else
			paddle.colorCode = 6;
	}

	if (((cursor.x > paddle.rightArrow.v2.x && cursor.x < paddle.rightArrow.v1.x)
		&&
		(cursor.y > paddle.rightArrow.v2.y && cursor.y < paddle.rightArrow.v3.y)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (paddle.colorCode < 6)
			paddle.colorCode++;
		else
			paddle.colorCode = 0;
	}
}
/*
void GeneratePowerUp()
{
	if (!paddle.powerUp.spawned)
	{
		if (powerUp.timer == powerUp.timerGoal)
		{
			powerUp.spawned = true;
			powerUp.timer = 0;
			powerUp.timerGoal = 8;
		}
	}
	else
	{
		if (!powerUp.active)
		{
			//Si la pelota colisiona con el PU -> active = true, timer = 0, timerGoal = 60 * 8

			if (powerUp.timer == powerUp.timerGoal)
				powerUp.spawned = false;
		}
		else
		{
			//Definir qué PU se activa
			//Definir si es bueno o malo
			//Aplicarlo al jugador que corresponda

			if (powerUp.timer == powerUp.timerGoal)
			{

			}
		}
	}

	powerUp.timer++;
}*/