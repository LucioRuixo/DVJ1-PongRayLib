#include "Game.h"
#include "Main Menu.h"
#include "Gameplay.h"
#include "Game Over.h"
#include "Paddles.h"
#include "Ball.h"

void Game()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		BeginDrawing();

		InitGame();
		InitPaddle(paddle1);
		InitPaddle(paddle2);
		InitBall();

		switch (currentState)
		{
		case GameState::MainMenu:
		case GameState::SelectionMenu:
		{
			MainMenu();
		}
		case GameState::PvP:
		case GameState::PvIA:
		{
			Gameplay();
		}
		case GameState::GameOver:
		{
			GameOver();
		}
		}

		EndDrawing();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();           // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
}

void InitGame()
{
	jVsJButton.width = 220;
	jVsJButton.height = 30;
	jVsJButton.x = screenWidth / 2 - 100;
	jVsJButton.y = screenHeight / 2 + 45;

	jVsIAButton.width = 160;
	jVsIAButton.height = 30;
	jVsIAButton.x = screenWidth / 2 - 70;
	jVsIAButton.y = screenHeight / 2 + 80;

	salirButton.width = 60;
	salirButton.height = 30;
	salirButton.x = screenWidth / 2 - 20;
	salirButton.y = screenHeight / 2 + 115;

	jugarButton.width = 80;
	jugarButton.height = 30;
	jugarButton.x = screenWidth / 2 - 35;
	jugarButton.y = screenHeight / 2 + 45;

	volverAndPausaButton.width = 95;
	volverAndPausaButton.height = 30;
	volverAndPausaButton.x = 10;
	volverAndPausaButton.y = 10;

	pauseMenu.width = 315;
	pauseMenu.height = 130;
	pauseMenu.x = screenWidth / 2 - pauseMenu.width / 2;
	pauseMenu.y = screenHeight / 2 - pauseMenu.height / 2;

	continuarButton.width = 110;
	continuarButton.height = 30;
	continuarButton.x = screenWidth / 2 - continuarButton.width / 2;
	continuarButton.y = screenHeight / 2 - continuarButton.height / 2 - ((pauseMenu.height - continuarButton.height * 3) / 4 + continuarButton.height);

	volverAlMdSButton.width = 295;
	volverAlMdSButton.height = 30;
	volverAlMdSButton.x = screenWidth / 2 - volverAlMdSButton.width / 2;
	volverAlMdSButton.y = screenHeight / 2 - volverAlMdSButton.height / 2;

	volverAlMPButton.width = 255;
	volverAlMPButton.height = 30;
	volverAlMPButton.x = screenWidth / 2 - volverAlMPButton.width / 2;
	volverAlMPButton.y = screenHeight / 2 - volverAlMPButton.height / 2 + ((pauseMenu.height - volverAlMPButton.height * 3) / 4 + volverAlMPButton.height);

	arrowLP1.width = 20;
	arrowLP1.height = 40;
	arrowLP1.x = paddle1.rec.x - 40;

	arrowRP1.width = 20;
	arrowRP1.height = 40;
	arrowRP1.x = paddle1.rec.x + paddle1.rec.width + 20;
	arrowRP1.y = (paddle1.rec.y + paddleHeight / 2) - 20;
	arrowLP1.y = (paddle1.rec.y + paddleHeight / 2) - 20;

	arrowLP2.width = 20;
	arrowLP2.height = 40;
	arrowLP2.x = paddle2.rec.x - 40;
	arrowLP2.y = (paddle1.rec.y + paddleHeight / 2) - 20;

	arrowRP2.width = 20;
	arrowRP2.height = 40;
	arrowRP2.x = paddle2.rec.x + paddle2.rec.width + 20;
	arrowRP2.y = (paddle2.rec.y + paddleHeight / 2) - 20;
}