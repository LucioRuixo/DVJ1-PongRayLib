#include "Game.h"

#include "Game Over.h"
#include "Gameplay.h"
#include "Main Menu.h"
#include "Paddles.h"

GameState currentState;
GameState selectedGameMode;

PowerUp powerUp;
//powerUp.good = (GetRandomValue(1, 2) == 1);

Vector2 cursor;

int randomN;
int point;

float screenWidth;
float screenHeight;

bool pauseMenuActive;
bool enterPressed;
bool paddle1LTH;

//----------------------------------------------------------------

static void InitGame();

namespace Game
{
void ExeGame()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	InitGame();

	InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		BeginDrawing();

		switch (currentState)
		{
		case GameState::MainMenu:
		case GameState::SelectionMenu:
		{
			ExeMainMenu();
		}
		case GameState::PvP:
		case GameState::PvIA:
		{
			ExeGameplay();
		}
		case GameState::GameOver:
		{
			ExeGameOver();
		}
		}

		EndDrawing();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();           // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
}
}

static void InitGame()
{
	currentState = GameState::MainMenu;

	IAPaddleSpeed = 5;

	screenWidth = 1360;
	screenHeight = 730;

	paddle1LastToHit = false;
	enterPressed = false;
}