#include "paddles.h"

#include "Game/game.h"

Paddle paddle1;
Paddle paddle2;

bool paddle1LastToHit;

//----------------------------------------------------------------

Paddle InitPaddle()
{
	Paddle paddle;

	paddle.color = RAYWHITE;

	paddle.rec.width = paddleWidth;
	paddle.rec.height = paddleHeight;
	paddle.rec.y = screenHeight / 2 - paddleHeight / 2;

	paddle.speed = paddleSpeed;

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

void ApplyPowerUp(Paddle &positivePaddle, Paddle &negativePaddle)
{
	switch (powerUp.type)
	{
	case PowerUpType::Bigger:
		positivePaddle.rec.height *= 2;
		break;
	case PowerUpType::Smaller:
		negativePaddle.rec.height /= 1.5;
		break;
	case PowerUpType::Speedier:
		positivePaddle.speed *= 2;
		break;
	case PowerUpType::LessSpeedy:
		negativePaddle.speed /= 2;
		break;
	case PowerUpType::Shield:
		shieldActive = true;
		InitShield();
		break;
	}
}

void RemovePowerUp(Paddle &positivePaddle, Paddle &negativePaddle)
{
	switch (powerUp.type)
	{
	case PowerUpType::Bigger:
		positivePaddle.rec.height = paddleHeight;
		break;
	case PowerUpType::Smaller:
		negativePaddle.rec.height = paddleHeight;
		break;
	case PowerUpType::Speedier:
		positivePaddle.speed = paddleSpeed;
		break;
	case PowerUpType::LessSpeedy:
		negativePaddle.speed = paddleSpeed;
		break;
	case PowerUpType::Shield:
		shieldActive = false;
		break;
	}
}