#ifndef POWER_UPS_H
#define POWER_UPS_H

#include "raylib.h"

#include "Game/States/gameplay.h"

const int powerUpHeight = 50;
const int powerUpWidth = 50;
const int spawnTimerMin = 5;
const int spawnTimerMax = 15;
const int xMin = screenWidth / 4;
const int xMax = (screenWidth / 4) * 3 - powerUpWidth;
const int yMin = gameplayScreenMinY;
const int yMax = screenHeight - powerUpHeight;

enum PowerUpType
{
	Bigger,
	Smaller,
	Speedier,
	LessSpeedy,
	Shield
};

struct PowerUp
{
	Color color;
	Rectangle rec;
	PowerUpType type;

	float timer;
	float timerGoal;

	bool active;
	bool good;
};

void InitPowerUp(PowerUp &powerUp);
void GeneratePowerUp();

#endif