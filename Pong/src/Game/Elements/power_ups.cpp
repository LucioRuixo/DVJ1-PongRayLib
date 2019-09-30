#include "power_ups.h"

void InitPowerUp(PowerUp &powerUp)
{
	powerUp.rec.height = 50;
	powerUp.rec.width = 50;
	powerUp.rec.x = GetRandomValue(xMin, xMax);
	powerUp.rec.y = GetRandomValue(yMin, yMax);
	powerUp.type = static_cast<PowerUpType>(GetRandomValue(0, 4));

	powerUp.timer = 0;
	powerUp.timerGoal = 15;

	powerUp.active = false;
	GetRandomValue(0, 1) ? powerUp.good = true : powerUp.good = false;
	powerUp.good ? powerUp.color = GREEN : powerUp.color = RED;
}