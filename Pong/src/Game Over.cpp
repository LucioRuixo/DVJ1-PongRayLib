#include "Game Over.h"

#include "Game.h"
#include "Buttons.h"
#include "Paddles.h"

namespace Game_Over
{
static void Init();
static void Update();
static void Draw();

void Execute()
{
	Init();
	
	while (!WindowShouldClose() && currentState == GameState::GameOver)
	{
		ClearBackground(BLACK);
		
		Update();

		Draw();

		EndDrawing();
	}
}

static void Init()
{
	InitGameOverButtons(volverAlMdSButton, volverAlMPButton);
}

static void Update()
{
	cursor = GetMousePosition();

	if (paddle1.score == 21)
		DrawText("HA GANADO EL JUGADOR 1!", screenWidth / 2 - 140, screenHeight / 2 - 50, 20, RAYWHITE);
	else
		DrawText("HA GANADO EL JUGADOR 2!", screenWidth / 2 - 140, screenHeight / 2 - 50, 20, RAYWHITE);

	//Volver a jugar
	if ((cursor.x > volverAlMdSButton.x && cursor.x < volverAlMdSButton.x + volverAlMdSButton.width)
		&&
		(cursor.y > volverAlMdSButton.y && cursor.y < volverAlMdSButton.y + volverAlMdSButton.height))
	{
		DrawRectangle(static_cast<int>(volverAlMdSButton.x), static_cast<int>(volverAlMdSButton.y), static_cast<int>(volverAlMdSButton.width), static_cast<int>(volverAlMdSButton.height), RAYWHITE);
		DrawText("Volver a jugar", static_cast<int>(volverAlMdSButton.x + 70), static_cast<int>(volverAlMdSButton.y + 5), 20, BLACK);
	}
	else
		DrawText("Volver a jugar", static_cast<int>(volverAlMdSButton.x + 70), static_cast<int>(volverAlMdSButton.y + 5), 20, RAYWHITE);
	if (((cursor.x > volverAlMdSButton.x && cursor.x < volverAlMdSButton.x + volverAlMdSButton.width)
		&&
		(cursor.y > volverAlMdSButton.y && cursor.y < volverAlMdSButton.y + volverAlMdSButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		pauseMenuActive = false;
		currentState = GameState::SelectionMenu;
	}

	//Volver al menú principal
	if ((cursor.x > volverAlMPButton.x && cursor.x < volverAlMPButton.x + volverAlMPButton.width)
		&&
		(cursor.y > volverAlMPButton.y && cursor.y < volverAlMPButton.y + volverAlMPButton.height))
	{
		DrawRectangle(static_cast<int>(volverAlMPButton.x), static_cast<int>(volverAlMPButton.y), static_cast<int>(volverAlMPButton.width), static_cast<int>(volverAlMPButton.height), RAYWHITE);
		DrawText("Volver al menu principal", static_cast<int>(volverAlMPButton.x + 5), static_cast<int>(volverAlMPButton.y + 5), 20, BLACK);
	}
	else
		DrawText("Volver al menu principal", static_cast<int>(volverAlMPButton.x + 5), static_cast<int>(volverAlMPButton.y + 5), 20, RAYWHITE);
	if (((cursor.x > volverAlMPButton.x && cursor.x < volverAlMPButton.x + volverAlMPButton.width)
		&&
		(cursor.y > volverAlMPButton.y && cursor.y < volverAlMPButton.y + volverAlMPButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		pauseMenuActive = false;
		currentState = GameState::MainMenu;
	}
}

static void Draw()
{

}
}