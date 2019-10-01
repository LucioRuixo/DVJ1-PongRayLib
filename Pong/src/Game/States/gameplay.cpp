#include "gameplay.h"

#include "Game/game.h"
#include "Game/Elements/ball.h"
#include "Game/Elements/buttons.h"
#include "Game/Elements/paddles.h"

int point;

bool pauseActive;

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
	pauseActive = false;
	powerUpSpawned = false;

	InitBall();
}

//Update
static void Update()
{
	cursor = GetMousePosition();

	GenerateButton(pause);

	if (!pauseActive)
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
		if (IsKeyDown(KEY_W))
		{
			paddle1.rec.y -= paddle1.speed * deltaTime;
			paddle1.up = true;
		}
		if (IsKeyDown(KEY_S))
		{
			paddle1.rec.y += paddle1.speed * deltaTime;
			paddle1.up = false;
		}
	}

	if (paddle1.rec.y < gameplayScreenMinY)
		paddle1.rec.y = gameplayScreenMinY;
	if (paddle1.rec.y + paddleHeight > screenHeight - 1)
		paddle1.rec.y = (screenHeight - 1) - paddleHeight;

	paddle1.center = paddle1.rec.y + paddle1.rec.height / 2;

	//Paleta 2
	if (currentState == GameState::PvP)
	{
		if (IsKeyDown(KEY_UP) || (IsKeyDown(KEY_DOWN)))
		{
			if (IsKeyDown(KEY_UP))
			{
				paddle2.rec.y -= paddle2.speed * deltaTime;
				paddle2.up = true;
			}
			if (IsKeyDown(KEY_DOWN))
			{
				paddle2.rec.y += paddle2.speed * deltaTime;
				paddle2.up = false;
			}
		}
	}
	else
	{
		if (ball.position.x > (screenWidth - 1) / 2)
		{
			if (ball.up)
			{
				if (paddle2.rec.y > ball.position.y)
					paddle2.rec.y -= paddle2.speed * deltaTime;
			}
			else
			{
				if (paddle2.rec.y < ball.position.y)
					paddle2.rec.y += paddle2.speed * deltaTime;
			}
		}
	}

	if (paddle2.rec.y < gameplayScreenMinY)
		paddle2.rec.y = gameplayScreenMinY;
	if (paddle2.rec.y + paddleHeight > screenHeight - 1)
		paddle2.rec.y = (screenHeight - 1) - paddleHeight;

	paddle2.center = paddle2.rec.y + paddle2.rec.height / 2;
}

static void UpdateBall()
{
	if (static_cast<float>(ball.position.y - ball.radius) <= static_cast<float>(gameplayScreenMinY))
		ball.up = false;
	if (static_cast<float>(ball.position.y + ball.radius)
		>= static_cast<float>(screenHeight - 1))
		ball.up = true;

	ball.up ? ball.position.y -= ball.direction.y * deltaTime : ball.position.y += ball.direction.y * deltaTime;
	ball.right ? ball.position.x += ball.direction.x * deltaTime : ball.position.x -= ball.direction.x * deltaTime;

	ball.direction.x += ballSpeedIncrease * deltaTime;

	if (ball.position.x + ball.radius < 0 || ball.position.x - ball.radius > screenWidth - 1)
	{
		if (ball.position.x + ball.radius < 0)
			paddle2.score++;
		else
			paddle1.score++;

		point++;

		InitBall();
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

		ball.color = paddle1.color;

		if (!powerUpSpawned)
			paddle1LastToHit = true;

		paddle1.center = paddle1.rec.y + paddle1.rec.height / 2;

		paddle1.ballAndCenterDiference = paddle1.center - ball.position.y;

		ball.direction.y = ball.direction.x * ((paddle1.rec.height / 2) / 10000 * paddle1.ballAndCenterDiference);
	}

	if (CheckCollisionCircleRec({ ball.position.x, ball.position.y }, static_cast<float>(ball.radius), paddle2.rec))
	{
		ball.right = false;

		ball.color = paddle2.color;

		if (!powerUpSpawned)
			paddle1LastToHit = false;

		paddle2.center = paddle2.rec.y + paddle2.rec.height / 2;

		paddle2.ballAndCenterDiference = paddle2.center - ball.position.y;

		ball.direction.y = ball.direction.x * ((paddle2.rec.height / 2) / 10000 * paddle2.ballAndCenterDiference);
	}

	if (shieldActive)
	{
		if (CheckCollisionCircleRec(ball.position, static_cast<float>(ball.radius), shield.rec))
			ball.right ? ball.right = false : ball.right = true;
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

	DrawRectangleV({ paddle1.rec.x, paddle1.rec.y }, { paddle1.rec.width, paddle1.rec.height }, paddle1.color);
	DrawRectangleV({ paddle2.rec.x, paddle2.rec.y }, { paddle2.rec.width, paddle2.rec.height }, paddle2.color);

	DrawCircleV(ball.position, static_cast<float>(ball.radius), ball.color);
	
	if (shieldActive)
	{
		DrawRectangle(static_cast<int>(shield.rec.x), static_cast<int>(shield.rec.y), static_cast<int>(shield.rec.width), static_cast<int>(shield.rec.height), shield.color);
	}

	if (pauseActive)
	{
		DrawRectangle(static_cast<int>(pauseMenu.rec.x), static_cast<int>(pauseMenu.rec.y), static_cast<int>(pauseMenu.rec.width), static_cast<int>(pauseMenu.rec.height), BLACK);
		DrawRectangleLines(static_cast<int>(pauseMenu.rec.x), static_cast<int>(pauseMenu.rec.y), static_cast<int>(pauseMenu.rec.width), static_cast<int>(pauseMenu.rec.height), RAYWHITE);

		GenerateButton(continue_);

		GenerateButton(returnToSelectionMenu);

		GenerateButton(returnToMainMenu);
	}
}
}