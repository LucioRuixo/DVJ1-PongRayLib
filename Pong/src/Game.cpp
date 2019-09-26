#include "Game.h"

#include "Game Over.h"
#include "Gameplay_PvAI.h"
#include "Gameplay_PvP.h"
#include "Main Menu.h"
#include "Selection Menu.h"
#include "Buttons.h"
#include "Paddles.h"

GameState currentState;
GameState selectedGameMode;

PowerUp powerUp;
//powerUp.good = (GetRandomValue(1, 2) == 1);

Vector2 cursor;

int randomN;
int point;

bool pauseState;
bool enterPressed;
bool paddle1LTH;

//----------------------------------------------------------------

namespace Game_
{
static void Init();

void Execute()
{
	Init();
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
		case GameState::PvAI:
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

static void Init()
{
	currentState = GameState::MainMenu;

	IAPaddleSpeed = 5;

	paddle1LastToHit = false;
	pauseState = false;
	enterPressed = false;

	InitMainMenuButtons(jugadorVsIA, jugadorVsJugador, pantallaCompleta, salir);
	InitSelectionMenuButtons(jugar, volver);
	InitGameplayAndGameOverButtons(continuar, pausa, pauseMenu, volverAlMenuDeSeleccion, volverAlMenuPrincipal);
}
}