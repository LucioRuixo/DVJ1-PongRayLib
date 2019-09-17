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

GameState currentState = GameState::MainMenu;
GameState selectedGameMode;

PowerUp powerUp;
//powerUp.good = (GetRandomValue(1, 2) == 1);

Vector2 cursor;

Rectangle jVsJButton;

Rectangle jVsIAButton;

Rectangle salirButton;

Rectangle jugarButton;

Rectangle volverAndPausaButton;

Rectangle pauseMenu;
bool pauseMenuActive = false;

Rectangle continuarButton;

Rectangle volverAlMdSButton;

Rectangle volverAlMPButton;

Rectangle arrowLP1;
Rectangle arrowRP1;
Rectangle arrowLP2;
Rectangle arrowRP2;

int randomN = GetRandomValue(1, 2);
int point = randomN;

bool enterPressed = false;

void Game();
void InitGame();

#endif