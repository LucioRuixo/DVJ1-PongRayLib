#include "Game.h"
#include "Game Over.h"
#include "Paddles.h"

void ExeGameOver()
{
	switch (currentState)
	{
	case GameState::GameOver:
	{
		while (!WindowShouldClose() && currentState == GameState::GameOver)
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
				DrawRectangle((int)volverAlMdSButton.x, (int)volverAlMdSButton.y, (int)volverAlMdSButton.width, (int)volverAlMdSButton.height, RAYWHITE);
				DrawText("Volver a jugar", (int)volverAlMdSButton.x + 70, (int)volverAlMdSButton.y + 5, 20, BLACK);
			}
			else
				DrawText("Volver a jugar", (int)volverAlMdSButton.x + 70, (int)volverAlMdSButton.y + 5, 20, RAYWHITE);
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
				DrawRectangle((int)volverAlMPButton.x, (int)volverAlMPButton.y, (int)volverAlMPButton.width, (int)volverAlMPButton.height, RAYWHITE);
				DrawText("Volver al menu principal", (int)volverAlMPButton.x + 5, (int)volverAlMPButton.y + 5, 20, BLACK);
			}
			else
				DrawText("Volver al menu principal", (int)volverAlMPButton.x + 5, (int)volverAlMPButton.y + 5, 20, RAYWHITE);
			if (((cursor.x > volverAlMPButton.x && cursor.x < volverAlMPButton.x + volverAlMPButton.width)
				&&
				(cursor.y > volverAlMPButton.y && cursor.y < volverAlMPButton.y + volverAlMPButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				pauseMenuActive = false;
				currentState = GameState::MainMenu;
			}

			EndDrawing();
			ClearBackground(BLACK);
		}

		break;
	}
	}
}