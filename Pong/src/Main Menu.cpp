#include "Main Menu.h"
#include "Paddles.h"

void MainMenu()
{
	switch (currentState)
	{
	case GameState::MainMenu:
	{
		while (!WindowShouldClose() && currentState == GameState::MainMenu)
		{
			cursor = GetMousePosition();

			DrawText("PONG!", screenWidth / 2 - 175, screenHeight / 2 - 70, 20, RAYWHITE);
			DrawText("Controles P1: W & S", screenWidth / 2 - 175, screenHeight / 2 - 45, 20, RAYWHITE);
			DrawText("Controles P2: flechas Arriba y Abajo", screenWidth / 2 - 175, screenHeight / 2 - 20, 20, RAYWHITE);
			DrawText("El primero que llegue a 21 puntos gana.", screenWidth / 2 - 175, screenHeight / 2 + 5, 20, RAYWHITE);

			//Jugador vs. Jugador
			if ((cursor.x > jVsJButton.x && cursor.x < jVsJButton.x + jVsJButton.width)
				&&
				(cursor.y > jVsJButton.y && cursor.y < jVsJButton.y + jVsJButton.height))
			{
				DrawRectangle((int)jVsJButton.x, (int)jVsJButton.y, (int)jVsJButton.width, (int)jVsJButton.height, RAYWHITE);
				DrawText("Jugador vs. Jugador", (int)jVsJButton.x + 5, (int)jVsJButton.y + 5, 20, BLACK);
			}
			else
				DrawText("Jugador vs. Jugador", (int)jVsJButton.x + 5, (int)jVsJButton.y + 5, 20, RAYWHITE);
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
				DrawRectangle((int)jVsIAButton.x, (int)jVsIAButton.y, (int)jVsIAButton.width, (int)jVsIAButton.height, RAYWHITE);
				DrawText("Jugador vs. IA", (int)jVsIAButton.x + 5, (int)jVsIAButton.y + 5, 20, BLACK);
			}
			else
				DrawText("Jugador vs. IA", (int)jVsIAButton.x + 5, (int)jVsIAButton.y + 5, 20, RAYWHITE);
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
				DrawRectangle((int)salirButton.x, (int)salirButton.y, (int)salirButton.width, (int)salirButton.height, RAYWHITE);
				DrawText("Salir", (int)salirButton.x + 5, (int)salirButton.y + 5, 20, BLACK);
			}
			else
				DrawText("Salir", (int)salirButton.x + 5, (int)salirButton.y + 5, 20, RAYWHITE);
			if (((cursor.x > salirButton.x && cursor.x < salirButton.x + salirButton.width)
				&&
				(cursor.y > salirButton.y && cursor.y < salirButton.y + salirButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				CloseWindow();
			}

			EndDrawing();
			ClearBackground(BLACK);
		}

		break;
	}

	case GameState::SelectionMenu:
	{
		InitPaddle(paddle1);
		InitPaddle(paddle2);
		paddle1.score = 0;
		paddle2.score = 0;

		while (!WindowShouldClose() && currentState == GameState::SelectionMenu)
		{
			cursor = GetMousePosition();

			//Volver
			if ((cursor.x > volverAndPausaButton.x && cursor.x < volverAndPausaButton.x + volverAndPausaButton.width)
				&&
				(cursor.y > volverAndPausaButton.y && cursor.y < volverAndPausaButton.y + volverAndPausaButton.height))
			{
				DrawRectangle((int)volverAndPausaButton.x, (int)volverAndPausaButton.y, (int)volverAndPausaButton.width, (int)volverAndPausaButton.height, RAYWHITE);
				DrawText("< Volver", (int)volverAndPausaButton.x + 5, (int)volverAndPausaButton.y + 5, 20, BLACK);
			}
			else
				DrawText("< Volver", (int)volverAndPausaButton.x + 5, (int)volverAndPausaButton.y + 5, 20, RAYWHITE);
			if (((cursor.x > volverAndPausaButton.x && cursor.x < volverAndPausaButton.x + volverAndPausaButton.width)
				&&
				(cursor.y > volverAndPausaButton.y && cursor.y < volverAndPausaButton.y + volverAndPausaButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				currentState = GameState::MainMenu;

			DrawText("Seleccionen el color de las paletas.", screenWidth / 2 - 175, screenHeight / 2 - 45, 20, RAYWHITE);

			//JUGAR
			if ((cursor.x > jugarButton.x && cursor.x < jugarButton.x + jugarButton.width)
				&&
				(cursor.y > jugarButton.y && cursor.y < jugarButton.y + jugarButton.height))
			{
				DrawRectangle((int)jugarButton.x, (int)jugarButton.y, (int)jugarButton.width, (int)jugarButton.height, RAYWHITE);
				DrawText("JUGAR", (int)jugarButton.x + 5, (int)jugarButton.y + 5, 20, BLACK);
			}
			else
				DrawText("JUGAR", (int)jugarButton.x + 5, (int)jugarButton.y + 5, 20, RAYWHITE);
			if (((cursor.x > jugarButton.x && cursor.x < jugarButton.x + jugarButton.width)
				&&
				(cursor.y > jugarButton.y && cursor.y < jugarButton.y + jugarButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				powerUp.spawned = false;
				powerUp.active = false;
				powerUp.timer = 0;
				powerUp.timerGoal = GetRandomValue(minPUSpawnTimer, maxPUSpawnTimer);

				if (selectedGameMode == GameState::PvP)
					currentState = GameState::PvP;
				else
					currentState = GameState::PvIA;
			}

			//Flechas
			DrawTriangle(
				{ paddle1.rec.x - 20, (paddle1.rec.y + paddleHeight / 2) - 20 },
				{ paddle1.rec.x - 40, paddle1.rec.y + paddleHeight / 2 },
				{ paddle1.rec.x - 20, (paddle1.rec.y + paddleHeight / 2) + 20 },
				RAYWHITE);
			if (((cursor.x > arrowLP1.x && cursor.x < arrowLP1.x + arrowLP1.width)
				&&
				(cursor.y > arrowLP1.y && cursor.y < arrowLP1.y + arrowLP1.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (paddle1.colorCode > 0)
					paddle1.colorCode--;
				else
					paddle1.colorCode = 6;
			}

			DrawTriangle(
				{ paddle1.rec.x + paddleWidth + 40, paddle1.rec.y + paddleHeight / 2 },
				{ paddle1.rec.x + paddleWidth + 20, (paddle1.rec.y + paddleHeight / 2) - 20 },
				{ paddle1.rec.x + paddleWidth + 20, (paddle1.rec.y + paddleHeight / 2) + 20 },
				RAYWHITE);
			if (((cursor.x > arrowRP1.x && cursor.x < arrowRP1.x + arrowRP1.width)
				&&
				(cursor.y > arrowRP1.y && cursor.y < arrowRP1.y + arrowRP1.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (paddle1.colorCode < 6)
					paddle1.colorCode++;
				else
					paddle1.colorCode = 0;
			}

			DrawTriangle(
				{ paddle2.rec.x - 20, (paddle2.rec.y + paddleHeight / 2) - 20 },
				{ paddle2.rec.x - 40, paddle2.rec.y + paddleHeight / 2 },
				{ paddle2.rec.x - 20, (paddle2.rec.y + paddleHeight / 2) + 20 },
				RAYWHITE);
			if (((cursor.x > arrowLP2.x && cursor.x < arrowLP2.x + arrowLP2.width)
				&&
				(cursor.y > arrowLP2.y && cursor.y < arrowLP2.y + arrowLP2.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (paddle2.colorCode > 0)
					paddle2.colorCode--;
				else
					paddle2.colorCode = 6;
			}

			DrawTriangle(
				{ paddle2.rec.x + paddleWidth + 40, paddle2.rec.y + paddleHeight / 2 },
				{ paddle2.rec.x + paddleWidth + 20, (paddle2.rec.y + paddleHeight / 2) - 20 },
				{ paddle2.rec.x + paddleWidth + 20, (paddle2.rec.y + paddleHeight / 2) + 20 },
				RAYWHITE);
			if (((cursor.x > arrowRP2.x && cursor.x < arrowRP2.x + arrowRP2.width)
				&&
				(cursor.y > arrowRP2.y && cursor.y < arrowRP2.y + arrowRP2.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (paddle2.colorCode < 6)
					paddle2.colorCode++;
				else
					paddle2.colorCode = 0;
			}

			switch (paddle1.colorCode)
			{
			case 0:
				paddle1.color = RAYWHITE;
				break;
			case 1:
				paddle1.color = RED;
				break;
			case 2:
				paddle1.color = BLUE;
				break;
			case 3:
				paddle1.color = YELLOW;
				break;
			case 4:
				paddle1.color = GREEN;
				break;
			case 5:
				paddle1.color = ORANGE;
				break;
			case 6:
				paddle1.color = PURPLE;
				break;
			}

			switch (paddle2.colorCode)
			{
			case 0:
				paddle2.color = RAYWHITE;
				break;
			case 1:
				paddle2.color = RED;
				break;
			case 2:
				paddle2.color = BLUE;
				break;
			case 3:
				paddle2.color = YELLOW;
				break;
			case 4:
				paddle2.color = GREEN;
				break;
			case 5:
				paddle2.color = ORANGE;
				break;
			case 6:
				paddle2.color = PURPLE;
				break;
			}

			//Paletas
			DrawRectangleV({ paddle1.rec.x, paddle1.rec.y }, { paddleWidth, paddleHeight }, paddle1.color);
			DrawRectangleV({ paddle2.rec.x, paddle2.rec.y }, { paddleWidth, paddleHeight }, paddle2.color);

			EndDrawing();
			ClearBackground(BLACK);
		}

		break;
	}
	}
}