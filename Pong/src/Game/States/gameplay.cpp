#include "gameplay.h"

#include "Game/game.h"
#include "Game/Elements/ball.h"
#include "Game/Elements/buttons.h"
#include "Game/Elements/paddles.h"

int point;
int randomN;

bool pauseState;

static float powerUpSpawnTimer;
static float powerUpSpawnTimerGoal;

namespace Gameplay
{
static void Init();

static void Update();
static void UpdatePaddles();
static void UpdateBall();
static void UpdatePowerUp();
static void CheckCollisions();

static void Draw();

void Execute()
{
	Init();

	while (!WindowShouldClose() && currentState == GameState::PvP && (paddle1.score < 11 && paddle2.score < 11)
		   ||
		   !WindowShouldClose() && currentState == GameState::PvAI && (paddle1.score < 11 && paddle2.score < 11))
	{
		deltaTime = GetFrameTime();

		ClearBackground(BLACK);
			
		Update();

		Draw();

		EndDrawing();
	}
		
	if (paddle1.score >= 11 || paddle2.score >= 11)
		currentState = GameState::GameOver;
}

//Init
static void Init()
{
	powerUpSpawnTimer = 0;
	powerUpSpawnTimerGoal = static_cast<float>(GetRandomValue(spawnTimerMax, spawnTimerMax));

	paddle1LastToHit = false;
	pauseState = false;
	powerUpSpawned = false;

	InitBall(ball);
}

//Update
static void Update()
{
	cursor = GetMousePosition();

	GenerateButton(pausa);

	if (!pauseState)
	{
		UpdatePaddles();

		UpdateBall();

		UpdatePowerUp();

		CheckCollisions();
	}
}

static void UpdatePaddles()
{
	//Paleta 1
	if (IsKeyDown(KEY_W) || (IsKeyDown(KEY_S)))
	{
		paddle1.movement = true;

		if (IsKeyDown(KEY_W))
		{
			paddle1.rec.y -= paddleSpeed * deltaTime;
			paddle1.up = true;
		}
		if (IsKeyDown(KEY_S))
		{
			paddle1.rec.y += paddleSpeed * deltaTime;
			paddle1.up = false;
		}
	}
	else
		paddle1.movement = false;

	//Paleta 2
	if (currentState == GameState::PvP)
	{
		if (IsKeyDown(KEY_UP) || (IsKeyDown(KEY_DOWN)))
		{
			paddle2.movement = true;

			if (IsKeyDown(KEY_UP))
			{
				paddle2.rec.y -= paddleSpeed * deltaTime;
				paddle2.up = true;
			}
			if (IsKeyDown(KEY_DOWN))
			{
				paddle2.rec.y += paddleSpeed * deltaTime;
				paddle2.up = false;
			}
		}
		else
			paddle2.movement = false;
	}
	else
	{
		if (ball.position.x > (screenWidth - 1) / 2)
		{
			if (ball.up)
			{
				if (paddle2.rec.y > ball.position.y)
					paddle2.rec.y -= paddleSpeed * deltaTime;
			}
			else
			{
				if (paddle2.rec.y < ball.position.y)
					paddle2.rec.y += paddleSpeed * deltaTime;
			}
		}
	}

	if (paddle1.rec.y < gameplayScreenMinY)
		paddle1.rec.y = gameplayScreenMinY;
	if (paddle1.rec.y + paddleHeight > screenHeight - 1)
		paddle1.rec.y = (screenHeight - 1) - paddleHeight;
	if (paddle2.rec.y < gameplayScreenMinY)
		paddle2.rec.y = gameplayScreenMinY;
	if (paddle2.rec.y + paddleHeight > screenHeight - 1)
		paddle2.rec.y = (screenHeight - 1) - paddleHeight;
}

static void UpdateBall()
{
	if (ball.up)
		ball.position.y -= ball.direction.y * deltaTime;
	else
		ball.position.y += ball.direction.y * deltaTime;
	if (ball.right)
		ball.position.x += ball.direction.x * deltaTime;
	else
		ball.position.x -= ball.direction.x * deltaTime;

	if (ball.position.y - ball.radius <= gameplayScreenMinY)
		ball.up = false;
	if (ball.position.y + ball.radius >= screenHeight - 1)
		ball.up = true;

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
}

static void UpdatePowerUp()
{
	if (!powerUpSpawned)
	{
		if (powerUpSpawnTimer >= powerUpSpawnTimerGoal)
		{
			powerUpSpawnTimer = 0;

			powerUpSpawned = true;

			InitPowerUp();
		}

		powerUpSpawnTimer += deltaTime;
	}
	else
	{
		GeneratePowerUp();
	}
}

static void CheckCollisions()
{
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

		ball.color = paddle1.color;

		ball.direction.x += 0.25f * deltaTime;

		if (!powerUpSpawned)
			paddle1LastToHit = true;
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

		ball.color = paddle2.color;

		ball.direction.x += 0.25f * deltaTime;

		if (!powerUpSpawned)
			paddle1LastToHit = false;
	}
}

//Draw
static void Draw()
{
	DrawText("Objetivo: 11 pts.", screenWidth / 2 - 50, 10, 20, RAYWHITE);
	DrawText(TextFormat("%i", paddle1.score), 10, 40, 50, RAYWHITE);
	DrawText(TextFormat("%i", paddle2.score), screenWidth - 50, 40, 50, RAYWHITE);

	DrawLine(0, gameplayScreenMinY, screenWidth - 1, gameplayScreenMinY, RAYWHITE);
	DrawLine(0, screenHeight - 1, screenWidth - 1, screenHeight - 1, RAYWHITE);

	DrawRectangleV({ paddle1.rec.x, paddle1.rec.y }, { paddleWidth, paddleHeight }, paddle1.color);
	DrawRectangleV({ paddle2.rec.x, paddle2.rec.y }, { paddleWidth, paddleHeight }, paddle2.color);

	DrawCircleV(ball.position, static_cast<float>(ball.radius), ball.color);
	
	if (pauseState)
	{
		DrawRectangle(static_cast<int>(pauseMenu.rec.x), static_cast<int>(pauseMenu.rec.y), static_cast<int>(pauseMenu.rec.width), static_cast<int>(pauseMenu.rec.height), BLACK);
		DrawRectangleLines(static_cast<int>(pauseMenu.rec.x), static_cast<int>(pauseMenu.rec.y), static_cast<int>(pauseMenu.rec.width), static_cast<int>(pauseMenu.rec.height), RAYWHITE);

		GenerateButton(continuar);

		GenerateButton(volverAlMenuDeSeleccion);

		GenerateButton(volverAlMenuPrincipal);
	}
}
}