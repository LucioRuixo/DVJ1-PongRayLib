#ifndef GAME_H
#define GAME_H

#include "raylib.h"

const int screenWidth = 1300;
const int screenHeight = 700;
const int minPUSpawnTimer = 60 * 5;
const int maxPUSpawnTimer = 60 * 15;
const int paddleWidth = 20;
const int paddleHeight = 100;
const int paddleSpeed = 20;
const int minIAPaddleSpeed = 4;
const int maxIAPaddleSpeed = 9;

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
namespace Game
{
void ExeGame();
}

#endif