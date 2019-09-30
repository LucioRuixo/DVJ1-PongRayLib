#include "power_ups.h"

#include "Game/Elements/ball.h"
#include "Game/Elements/paddles.h"

PowerUp powerUp;

bool powerUpSpawned;

//----------------------------------------------------------------

void InitPowerUp()
{
	powerUp.rec.height = 50;
	powerUp.rec.width = 50;
	powerUp.rec.x = static_cast<float>(GetRandomValue(xMin, xMax));
	powerUp.rec.y = static_cast<float>(GetRandomValue(yMin, yMax));
	powerUp.type = static_cast<PowerUpType>(GetRandomValue(0, 4));

	powerUp.timer = 0;
	powerUp.timerGoal = 15;

	switch (powerUp.type)
	{
	case PowerUpType::Bigger:
		powerUp.text = "T++";
		break;
	case PowerUpType::Smaller:
		powerUp.text = "T--";
		break;
	case PowerUpType::Speedier:
		powerUp.text = "V++";
		break;
	case PowerUpType::LessSpeedy:
		powerUp.text = "V--";
		break;
	case PowerUpType::Shield:
		powerUp.text = "E";
		break;
	}

	powerUp.active = false;
	GetRandomValue(0, 1) ? powerUp.good = true : powerUp.good = false;
	powerUp.good ? powerUp.color = GREEN : powerUp.color = RED;
}

void GeneratePowerUp()
{
	if (!powerUp.active)
	{
		if (powerUp.timer < powerUp.timerGoal)
		{
			DrawPowerUp();

			if (CheckCollisionCircleRec(ball.position, static_cast<float>(ball.radius), powerUp.rec))
			{
				paddle1LastToHit ? ApplyPowerUp(paddle1) : ApplyPowerUp(paddle2);

				powerUp.timer = 0;

				powerUp.active = true;
			}
		}
		else
		{
			powerUp.timer = 0;

			powerUpSpawned = false;
		}
	}
	else
	{
		if (powerUp.timer >= powerUp.timerGoal)
		{
			paddle1LastToHit ? RemovePowerUp(paddle1) : RemovePowerUp(paddle2);

			powerUp.timer = 0;

			powerUpSpawned = false;
		}
	}

	powerUp.timer += deltaTime;
}

void DrawPowerUp()
{
	DrawRectangle(static_cast<int>(powerUp.rec.x), static_cast<int>(powerUp.rec.y), static_cast<int>(powerUp.rec.width), static_cast<int>(powerUp.rec.height), powerUp.color);

	DrawText(powerUp.text, static_cast<int>(powerUp.rec.x), static_cast<int>(powerUp.rec.y), 20, RAYWHITE);
}