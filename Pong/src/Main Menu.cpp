#include "Main Menu.h"

#include "Game.h"
#include "Buttons.h"

namespace Main_Menu
{
static void Init();
static void Update();
static void Draw();

void Execute()
{
	Init();

	while (!WindowShouldClose() && currentState == GameState::MainMenu)
	{
		ClearBackground(BLACK);

		Update();

		Draw();

		EndDrawing();
	}
}

static void Init()
{
	InitMainMenuButtons(pantallaCompletaButton, jVsJButton, jVsIAButton, salirButton);
}

static void Update()
{
	cursor = GetMousePosition();

	//Pantalla completa
	if ((cursor.x > pantallaCompletaButton.x && cursor.x < pantallaCompletaButton.x + pantallaCompletaButton.width)
		&&
		(cursor.y > pantallaCompletaButton.y && cursor.y < pantallaCompletaButton.y + pantallaCompletaButton.height))
	{
		DrawRectangle(static_cast<int>(pantallaCompletaButton.x), static_cast<int>(pantallaCompletaButton.y), static_cast<int>(pantallaCompletaButton.width), static_cast<int>(pantallaCompletaButton.height), RAYWHITE);
		DrawText("Pantalla completa", static_cast<int>(pantallaCompletaButton.x + 5), static_cast<int>(pantallaCompletaButton.y + 5), 20, BLACK);
	}
	else
		DrawText("Pantalla completa", static_cast<int>(pantallaCompletaButton.x + 5), static_cast<int>(pantallaCompletaButton.y + 5), 20, RAYWHITE);
	if (((cursor.x > pantallaCompletaButton.x && cursor.x < pantallaCompletaButton.x + pantallaCompletaButton.width)
		&&
		(cursor.y > pantallaCompletaButton.y && cursor.y < pantallaCompletaButton.y + pantallaCompletaButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		ToggleFullscreen();
	}

	//Jugador vs. Jugador
	if ((cursor.x > jVsJButton.x && cursor.x < jVsJButton.x + jVsJButton.width)
		&&
		(cursor.y > jVsJButton.y && cursor.y < jVsJButton.y + jVsJButton.height))
	{
		DrawRectangle(static_cast<int>(jVsJButton.x), static_cast<int>(jVsJButton.y), static_cast<int>(jVsJButton.width), static_cast<int>(jVsJButton.height), RAYWHITE);
		DrawText("Jugador vs. Jugador", static_cast<int>(jVsJButton.x + 5), static_cast<int>(jVsJButton.y + 5), 20, BLACK);
	}
	else
		DrawText("Jugador vs. Jugador", static_cast<int>(jVsJButton.x + 5), static_cast<int>(jVsJButton.y + 5), 20, RAYWHITE);
	if (((cursor.x > jVsJButton.x && cursor.x < jVsJButton.x + jVsJButton.width)
		&&
		(cursor.y > jVsJButton.y && cursor.y < jVsJButton.y + jVsJButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		selectedGameMode = GameState::PvP;
		currentState = GameState::SelectionMenu;
	}

	//Jugador vs. IA
	if ((cursor.x > jVsIAButton.x && cursor.x < jVsIAButton.x + jVsIAButton.width)
		&&
		(cursor.y > jVsIAButton.y && cursor.y < jVsIAButton.y + jVsIAButton.height))
	{
		DrawRectangle(static_cast<int>(jVsIAButton.x), static_cast<int>(jVsIAButton.y), static_cast<int>(jVsIAButton.width), static_cast<int>(jVsIAButton.height), RAYWHITE);
		DrawText("Jugador vs. IA", static_cast<int>(jVsIAButton.x + 5), static_cast<int>(jVsIAButton.y + 5), 20, BLACK);
	}
	else
		DrawText("Jugador vs. IA", static_cast<int>(jVsIAButton.x + 5), static_cast<int>(jVsIAButton.y + 5), 20, RAYWHITE);
	if (((cursor.x > jVsIAButton.x && cursor.x < jVsIAButton.x + jVsIAButton.width)
		&&
		(cursor.y > jVsIAButton.y && cursor.y < jVsIAButton.y + jVsIAButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		selectedGameMode = GameState::PvIA;
		currentState = GameState::SelectionMenu;
	}

	//Salir
	if ((cursor.x > salirButton.x && cursor.x < salirButton.x + salirButton.width)
		&&
		(cursor.y > salirButton.y && cursor.y < salirButton.y + salirButton.height))
	{
		DrawRectangle(static_cast<int>(salirButton.x), static_cast<int>(salirButton.y), static_cast<int>(salirButton.width), static_cast<int>(salirButton.height), RAYWHITE);
		DrawText("Salir", static_cast<int>(salirButton.x + 5), static_cast<int>(salirButton.y + 5), 20, BLACK);
	}
	else
		DrawText("Salir", static_cast<int>(salirButton.x + 5), static_cast<int>(salirButton.y + 5), 20, RAYWHITE);
	if (((cursor.x > salirButton.x && cursor.x < salirButton.x + salirButton.width)
		&&
		(cursor.y > salirButton.y && cursor.y < salirButton.y + salirButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		CloseWindow();
	}
}

static void Draw()
{
	DrawText("PONG!", screenWidth / 2 - 175, screenHeight / 2 - 70, 20, RAYWHITE);
	DrawText("Controles P1: W & S", screenWidth / 2 - 175, screenHeight / 2 - 45, 20, RAYWHITE);
	DrawText("Controles P2: flechas Arriba y Abajo", screenWidth / 2 - 175, screenHeight / 2 - 20, 20, RAYWHITE);
	DrawText("El primero que llegue a 21 puntos gana.", screenWidth / 2 - 175, screenHeight / 2 + 5, 20, RAYWHITE);
}
}