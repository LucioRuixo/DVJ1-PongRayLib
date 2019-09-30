#include "game.h"

#include "Game/States/game_over.h"
#include "Game/States/gameplay.h"
#include "Game/States/main_menu.h"
#include "Game/States/selection_menu.h"
#include "Game/Elements/buttons.h"
#include "Game/Elements/paddles.h"

GameState currentState;
GameState selectedGameMode;

//powerUp.good = (GetRandomValue(1, 2) == 1);

Vector2 cursor;

float deltaTime;
bool enterPressed;

//----------------------------------------------------------------

namespace Game_
{
static void Init();

void Execute()
{
	Init();

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
		case GameState::PvAI:
		{
			Gameplay::Execute();
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

	deltaTime = 0;

	pauseState = false;
	enterPressed = false;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");
	InitMainMenuButtons(jugadorVsIA, jugadorVsJugador, pantallaCompleta, salir);
	InitSelectionMenuButtons(jugar, volver);
	InitGameplayAndGameOverButtons(continuar, pausa, pauseMenu, volverAlMenuDeSeleccion, volverAlMenuPrincipal);
}
}