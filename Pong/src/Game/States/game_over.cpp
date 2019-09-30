#include "game_over.h"

#include "Game/game.h"
#include "Game/Elements/buttons.h"
#include "Game/Elements/paddles.h"

namespace Game_Over
{
static void Update();
static void Draw();

void Execute()
{
	while (!WindowShouldClose() && currentState == GameState::GameOver)
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

	if (paddle1.score == 21)
		DrawText("HA GANADO EL JUGADOR 1!", screenWidth / 2 - 140, screenHeight / 2 - 50, 20, RAYWHITE);
	else
		DrawText("HA GANADO EL JUGADOR 2!", screenWidth / 2 - 140, screenHeight / 2 - 50, 20, RAYWHITE);

	GenerateButton(volverAlMenuDeSeleccion);

	GenerateButton(volverAlMenuPrincipal);
}

static void Draw()
{

}
}