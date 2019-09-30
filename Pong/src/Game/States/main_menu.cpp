#include "main_menu.h"

#include "Game/game.h"
#include "Game/Elements/buttons.h"

namespace Main_Menu
{
static void Update();
static void Draw();

void Execute()
{
	while (!WindowShouldClose() && currentState == GameState::MainMenu)
	{
		ClearBackground(BLACK);

		Update();

		Draw();

		EndDrawing();
	}
}

static void Update()
{
	cursor = GetMousePosition();

	GenerateButton(pantallaCompleta);

	GenerateButton(jugadorVsJugador);

	GenerateButton(jugadorVsIA);

	GenerateButton(salir);
}

static void Draw()
{
	DrawText("PONG!", screenWidth / 2 - 175, screenHeight / 2 - 70, 20, RAYWHITE);
	DrawText("Controles P1: W & S", screenWidth / 2 - 175, screenHeight / 2 - 45, 20, RAYWHITE);
	DrawText("Controles P2: flechas Arriba y Abajo", screenWidth / 2 - 175, screenHeight / 2 - 20, 20, RAYWHITE);
	DrawText("El primero que llegue a 21 puntos gana.", screenWidth / 2 - 175, screenHeight / 2 + 5, 20, RAYWHITE);
}
}