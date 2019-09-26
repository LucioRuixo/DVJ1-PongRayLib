#include "Gameplay_PvP.h"

#include "Game.h"
#include "Ball.h"
#include "Buttons.h"
#include "Paddles.h"

namespace Gameplay_PvP
{
static void Init();
static void Update();
static void Draw();

void Execute()
{
	Init();

	while (!WindowShouldClose() && currentState == GameState::PvP && (paddle1.score < 11 && paddle2.score < 11))
	{
		ClearBackground(BLACK);
			
		Update();

		Draw();

		EndDrawing();
	}
		
	if (paddle1.score >= 11 || paddle2.score >= 11)
		currentState = GameState::GameOver;
}

static void Init()
{
	InitBall(ball);
	InitGameplayButtons(jugarButton, volverAndPausaButton, pauseMenu, continuarButton, volverAlMdSButton, volverAlMPButton);
}

static void Update()
{
	// Input
	//----------------------------------------------------------------------------------
	cursor = GetMousePosition();

	//Pausa
	if ((cursor.x > volverAndPausaButton.x && cursor.x < volverAndPausaButton.x + volverAndPausaButton.width)
		&&
		(cursor.y > volverAndPausaButton.y && cursor.y < volverAndPausaButton.y + volverAndPausaButton.height))
	{
		DrawRectangle(static_cast<int>(volverAndPausaButton.x), static_cast<int>(volverAndPausaButton.y), static_cast<int>(volverAndPausaButton.width), static_cast<int>(volverAndPausaButton.height), RAYWHITE);
		DrawText("|| Pausa", static_cast<int>(volverAndPausaButton.x + 5), static_cast<int>(volverAndPausaButton.y + 5), 20, BLACK);
	}
	else
		DrawText("|| Pausa", static_cast<int>(volverAndPausaButton.x + 5), static_cast<int>(volverAndPausaButton.y + 5), 20, RAYWHITE);
	if (((cursor.x > volverAndPausaButton.x && cursor.x < volverAndPausaButton.x + volverAndPausaButton.width)
		&&
		(cursor.y > volverAndPausaButton.y && cursor.y < volverAndPausaButton.y + volverAndPausaButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		pauseMenuActive = true;

	if (!pauseMenuActive)
	{
		//Input de los jugadores
		if (IsKeyDown(KEY_W) || (IsKeyDown(KEY_S)))
		{
			paddle1.movement = true;

			if (IsKeyDown(KEY_W))
			{
				paddle1.rec.y -= paddleSpeed;
				paddle1.up = true;
			}
			if (IsKeyDown(KEY_S))
			{
				paddle1.rec.y += paddleSpeed;
				paddle1.up = false;
			}
		}
		else
			paddle1.movement = false;

		if (IsKeyDown(KEY_UP) || (IsKeyDown(KEY_DOWN)))
		{
			paddle2.movement = true;

			if (IsKeyDown(KEY_UP))
			{
				paddle2.rec.y -= paddleSpeed;
				paddle2.up = true;
			}
			if (IsKeyDown(KEY_DOWN))
			{
				paddle2.rec.y += paddleSpeed;
				paddle2.up = false;
			}
		}
		else
			paddle2.movement = false;
		//----------------------------------------------------------------------------------

		// Update
		//----------------------------------------------------------------------------------
		//Límites de las paletas
		if (paddle1.rec.y < 95)
			paddle1.rec.y = 95;
		if (paddle1.rec.y + paddleHeight > screenHeight - 1)
			paddle1.rec.y = (screenHeight - 1) - paddleHeight;
		if (paddle2.rec.y < 95)
			paddle2.rec.y = 95;
		if (paddle2.rec.y + paddleHeight > screenHeight - 1)
			paddle2.rec.y = (screenHeight - 1) - paddleHeight;

		//Límites en y de la pelota
		if (ball.position.y - ball.radius <= 95)
			ball.up = false;
		if (ball.position.y + ball.radius >= screenHeight - 1)
			ball.up = true;

		//Límites en x de la pelota
		if (ball.position.x + ball.radius < 0 || ball.position.x - ball.radius > screenWidth - 1)
		{
			if (ball.position.x + ball.radius < 0)
				paddle2.score++;
			else
				paddle1.score++;

			point++;

			ball.position = { screenWidth / 2, screenHeight / 2 };
			ball.direction = { static_cast<float>(GetRandomValue(static_cast<int>(minBallSpeed), static_cast<int>(maxBallSpeed - 1))), maxBallSpeed - ball.direction.x };

			randomN = GetRandomValue(1, 2);
			if (randomN == 1)
				ball.up = true;
			else
				ball.up = false;

			if (point % 2 == 0)
				ball.right = true;
			else
				ball.right = false;
		}

		//Colisión entre pelota y paleta
		if (CheckCollisionCircleRec({ ball.position.x, ball.position.y }, static_cast<float>(ball.radius), paddle1.rec))
		{
			ball.right = true;

			if (paddle1.movement)
			{
				if (!paddle1.up)
					ball.up = true;
				else
					ball.up = false;
			}

			paddle1LTH = true;
			ball.direction.x += 0.25f;
			ball.color = paddle1.color;
		}
		if (CheckCollisionCircleRec({ ball.position.x, ball.position.y }, static_cast<float>(ball.radius), paddle2.rec))
		{
			ball.right = false;

			if (paddle2.movement)
			{
				if (!paddle2.up)
					ball.up = true;
				else
					ball.up = false;
			}

			paddle1LTH = false;
			ball.direction.x += 0.25f;
			ball.color = paddle2.color;
		}

		//Movimiento de la pelota
		if (ball.up)
			ball.position.y -= ball.direction.y;
		else
			ball.position.y += ball.direction.y;
		if (ball.right)
			ball.position.x += ball.direction.x;
		else
			ball.position.x -= ball.direction.x;

		//Power-Ups
		if (!powerUp.spawned)
		{
			if (powerUp.timer == powerUp.timerGoal)
			{
				powerUp.spawned = true;
				powerUp.timer = 0;
				powerUp.timerGoal = 8;
			}
		}
		else
		{
			if (!powerUp.active)
			{
				//Si la pelota colisiona con el PU -> active = true, timer = 0, timerGoal = 60 * 8

				if (powerUp.timer == powerUp.timerGoal)
					powerUp.spawned = false;
			}
			else
			{
				//Definir qué PU se activa
				//Definir si es bueno o malo
				//Aplicarlo al jugador que corresponda

				if (powerUp.timer == powerUp.timerGoal)
				{

				}
			}
		}
		powerUp.timer++;
	}
	else
	{
		DrawRectangle(static_cast<int>(pauseMenu.x), static_cast<int>(pauseMenu.y), static_cast<int>(pauseMenu.width), static_cast<int>(pauseMenu.height), BLACK);
		DrawRectangleLines(static_cast<int>(pauseMenu.x), static_cast<int>(pauseMenu.y), static_cast<int>(pauseMenu.width), static_cast<int>(pauseMenu.height), RAYWHITE);

		//Continuar
		if ((cursor.x > continuarButton.x && cursor.x < continuarButton.x + continuarButton.width)
			&&
			(cursor.y > continuarButton.y && cursor.y < continuarButton.y + continuarButton.height))
		{
			DrawRectangle(static_cast<int>(continuarButton.x), static_cast<int>(continuarButton.y), static_cast<int>(continuarButton.width), static_cast<int>(continuarButton.height), RAYWHITE);
			DrawText("Continuar", static_cast<int>(continuarButton.x + 5), static_cast<int>(continuarButton.y + 5), 20, BLACK);
		}
		else
			DrawText("Continuar", static_cast<int>(continuarButton.x + 5), static_cast<int>(continuarButton.y + 5), 20, RAYWHITE);
		if (((cursor.x > continuarButton.x && cursor.x < continuarButton.x + continuarButton.width)
			&&
			(cursor.y > continuarButton.y && cursor.y < continuarButton.y + continuarButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			pauseMenuActive = false;

		//Volver al menú de selección
		if ((cursor.x > volverAlMdSButton.x && cursor.x < volverAlMdSButton.x + volverAlMdSButton.width)
			&&
			(cursor.y > volverAlMdSButton.y && cursor.y < volverAlMdSButton.y + volverAlMdSButton.height))
		{
			DrawRectangle(static_cast<int>(volverAlMdSButton.x), static_cast<int>(volverAlMdSButton.y), static_cast<int>(volverAlMdSButton.width), static_cast<int>(volverAlMdSButton.height), RAYWHITE);
			DrawText("Volver al menu de seleccion", static_cast<int>(volverAlMdSButton.x + 5), static_cast<int>(volverAlMdSButton.y + 5), 20, BLACK);
		}
		else
			DrawText("Volver al menu de seleccion", static_cast<int>(volverAlMdSButton.x + 5), static_cast<int>(volverAlMdSButton.y + 5), 20, RAYWHITE);
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
}

static void Draw()
{
	DrawText("Objetivo: 11 pts.", screenWidth / 2 - 50, 10, 20, RAYWHITE);
	DrawText(TextFormat("%i", paddle1.score), 10, 40, 50, RAYWHITE);
	DrawText(TextFormat("%i", paddle2.score), screenWidth - 50, 40, 50, RAYWHITE);

	DrawLine(0, 95, screenWidth - 1, 95, RAYWHITE);
	DrawLine(0, screenHeight - 1, screenWidth - 1, screenHeight - 1, RAYWHITE);

	DrawRectangleV({ paddle1.rec.x, paddle1.rec.y }, { paddleWidth, paddleHeight }, paddle1.color);
	DrawRectangleV({ paddle2.rec.x, paddle2.rec.y }, { paddleWidth, paddleHeight }, paddle2.color);

	DrawCircleV(ball.position, static_cast<float>(ball.radius), ball.color);
}
}