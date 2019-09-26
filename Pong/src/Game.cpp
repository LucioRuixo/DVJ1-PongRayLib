#include "Game.h"

#include "Game Over.h"
#include "Gameplay_PvAI.h"
#include "Gameplay_PvP.h"
#include "Main Menu.h"
#include "Selection Menu.h"
#include "Paddles.h"

GameState currentState;
GameState selectedGameMode;

PowerUp powerUp;
//powerUp.good = (GetRandomValue(1, 2) == 1);

Vector2 cursor;

int randomN;
int point;

bool pauseMenuActive;
bool enterPressed;
bool paddle1LTH;

//----------------------------------------------------------------

static void InitGame();

namespace Game_
{
void Execute()
{
	InitGame();
	InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		switch (currentState)
		{
		case GameState::MainMenu:
		{
			Main_Menu::Execute();
		}
		case GameState::SelectionMenu:
		{
			Selection_Menu::Execute();
		}
		case GameState::PvP:
		{
			Gameplay_PvP::Execute();
		}
		case GameState::PvIA:
		{
			Gameplay_PvAI::Execute();
		}
		case GameState::GameOver:
		{
			Game_Over::Execute();
		}
		}

		EndDrawing();
	}

	CloseWindow();
}
}

static void InitGame()
{
	currentState = GameState::MainMenu;

	IAPaddleSpeed = 5;

	paddle1LastToHit = false;
	enterPressed = false;
}