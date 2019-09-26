#ifndef GAME_H
#define GAME_H

#include "raylib.h"

const int paddleSpeed = 20;
const int paddleWidth = 20;
const int paddleHeight = 100;
const int powerUpMinSpawnTimer = 60 * 5;
const int powerUpMaxSpawnTimer = 60 * 15;
const int screenWidth = 1280;
const int screenHeight = 720;
const int iAMinPaddleSpeed = 4;
const int iAMaxPaddleSpeed = 9;

enum GameState
{
	MainMenu,
	SelectionMenu,
	PvP,
	PvIA,
	GameOver
};

enum PowerUps
{
	Bigger,
	Smaller,
	Speedier,
	LessSpeedy,
	Shield
};

struct PowerUp
{
	Rectangle rec;
	PowerUps type;

	int timer;
	int timerGoal;

	bool spawned;
	bool active;
	bool good;
};

extern GameState currentState;
extern GameState selectedGameMode;

extern PowerUp powerUp;
//powerUp.good = (GetRandomValue(1, 2) == 1);

extern Vector2 cursor;

extern int randomN;
extern int point;

extern bool pauseMenuActive;
extern bool enterPressed;
extern bool paddle1LTH;

//----------------------------------------------------------------
namespace Game_
{
void Execute();
}

#endif