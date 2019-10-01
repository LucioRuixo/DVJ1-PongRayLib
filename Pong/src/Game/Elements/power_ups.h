#ifndef POWER_UPS_H
#define POWER_UPS_H

#include "raylib.h"

#include "Game/game.h"
#include "Game/States/gameplay.h"

const int powerUpHeight = 50;
const int powerUpWidth = 50;
const int shieldWidth = 5;
const int shieldHeight = 200;
const int spawnTimerMin = 3;
const int spawnTimerMax = 10;
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

	const char* text;

	bool active;
	bool good;
};

struct Shield_
{
	Color color;
	Rectangle rec;
};

extern PowerUp powerUp;
extern Shield_ shield;

extern bool powerUpSpawned;
extern bool shieldActive;

//----------------------------------------------------------------

void InitPowerUp();
void GeneratePowerUp();
void DrawPowerUp();

void InitShield();

#endif