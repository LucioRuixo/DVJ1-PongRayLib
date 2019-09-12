
/*******************************************************************************************
*
*   raylib [core] example - Keyboard input
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
*******************************************************************************************/

/*******************************************************************************************
*
*   PONG
*	
*	v1:
*   Controles para dos jugadores. X
*	Selección de color con click. X
*	Pintar la pelota del color del jugador que le pega. X
*
*	v2:
*	Powerups (+ velocidad, + tamaño, escudo).
*	Texturas.
*   IA. X (más o menos)
*   Sonido.
*
*******************************************************************************************/

#include "raylib.h"

const int screenWidth = 1300;
const int screenHeight = 700;
const int minPUSpawnTimer = 60 * 5;
const int maxPUSpawnTimer = 60 * 15;
const int paddleWidth = 20;
const int paddleHeight = 100;
const int paddleSpeed = 20;
const int minIAPaddleSpeed = 4;
const int maxIAPaddleSpeed = 9;
const int minBallSpeed = 15;
const int maxBallSpeed = 20;

enum GameState
{
	MainMenu,
	SelectionMenu,
	PvP,
	PvIA,
	GameOver
};

enum PowerUps
{
	Bigger,
	Smaller,
	Speedier,
	LessSpeedy,
	Shield
};

struct Paddle
{
	Rectangle rec;
	Color color = RAYWHITE;

	int score = 0;

	bool movement;
	bool up;
	bool right;
};

struct Ball
{
	Vector2 position;
	Vector2 direction;
	Color color = RAYWHITE;

	int radius = 15;

	bool up;
	bool right;
};

struct PowerUp
{
	Rectangle rec;
	PowerUps type;

	int timer;
	int timerGoal;

	bool spawned;
	bool active;
	bool good;
};

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

	GameState currentState = GameState::MainMenu;
	GameState selectedGameMode;

	Paddle paddle1;
	paddle1.rec.width = paddleWidth;
	paddle1.rec.height = paddleHeight;
	paddle1.rec.x = (float)(screenWidth / 20);
	paddle1.rec.y = (float)(screenHeight / 2 - paddleHeight / 2);
	int paddle1Color = 0;

	Paddle paddle2;
	paddle2.rec.width = paddleWidth;
	paddle2.rec.height = paddleHeight;
	paddle2.rec.x = (float)(screenWidth / 20 * 19 - paddleWidth);
	paddle2.rec.y = (float)(screenHeight / 2 - paddleHeight / 2);
	int paddle2Color = 0;

	float IAPaddleSpeed = 5.0f;
	bool paddle1LTH = true; //LTH = Last To Hit

	Ball ball;
	ball.position = {(float)screenWidth / 2, (float)screenHeight / 2};
	ball.direction.x = (float)GetRandomValue(minBallSpeed, maxBallSpeed - 1); ball.direction.y = (float)(maxBallSpeed - ball.direction.x);

	PowerUp powerUp;
	powerUp.good = (GetRandomValue(1, 2) == 1);

	Vector2 cursor;

	Rectangle jVsJButton;
	jVsJButton.width = 220;
	jVsJButton.height = 30;
	jVsJButton.x = screenWidth / 2 - 100;
	jVsJButton.y = screenHeight / 2 + 45;

	Rectangle jVsIAButton;
	jVsIAButton.width = 160;
	jVsIAButton.height = 30;
	jVsIAButton.x = screenWidth / 2 - 70;
	jVsIAButton.y = screenHeight / 2 + 80;

	Rectangle salirButton;
	salirButton.width = 60;
	salirButton.height = 30;
	salirButton.x = screenWidth / 2 - 20;
	salirButton.y = screenHeight / 2 + 115;

	Rectangle jugarButton;
	jugarButton.width = 80;
	jugarButton.height = 30;
	jugarButton.x = screenWidth / 2 - 35;
	jugarButton.y = screenHeight / 2 + 45;

	Rectangle volverAndPausaButton;
	volverAndPausaButton.width = 95;
	volverAndPausaButton.height = 30;
	volverAndPausaButton.x = 10;
	volverAndPausaButton.y = 10;

	Rectangle pauseMenu;
	pauseMenu.width = 315;
	pauseMenu.height = 130;
	pauseMenu.x = screenWidth / 2 - pauseMenu.width / 2;
	pauseMenu.y = screenHeight / 2 - pauseMenu.height / 2;
	bool pauseMenuActive = false;

	Rectangle continuarButton;
	continuarButton.width = 110;
	continuarButton.height = 30;
	continuarButton.x = screenWidth / 2 - continuarButton.width / 2;
	continuarButton.y = screenHeight / 2 - continuarButton.height / 2 - ((pauseMenu.height - continuarButton.height * 3) / 4 + continuarButton.height);

	Rectangle volverAlMdSButton;
	volverAlMdSButton.width = 295;
	volverAlMdSButton.height = 30;
	volverAlMdSButton.x = screenWidth / 2 - volverAlMdSButton.width / 2;
	volverAlMdSButton.y = screenHeight / 2 - volverAlMdSButton.height / 2;

	Rectangle volverAlMPButton;
	volverAlMPButton.width = 255;
	volverAlMPButton.height = 30;
	volverAlMPButton.x = screenWidth / 2 - volverAlMPButton.width / 2;
	volverAlMPButton.y = screenHeight / 2 - volverAlMPButton.height / 2 + ((pauseMenu.height - volverAlMPButton.height * 3) / 4 + volverAlMPButton.height);

	Rectangle arrowLP1;
	arrowLP1.width = 20;
	arrowLP1.height = 40;
	arrowLP1.x = paddle1.rec.x - 40;
	arrowLP1.y = (paddle1.rec.y + paddleHeight / 2) - 20;
	Rectangle arrowRP1;
	arrowRP1.width = 20;
	arrowRP1.height = 40;
	arrowRP1.x = paddle1.rec.x + paddle1.rec.width + 20;
	arrowRP1.y = (paddle1.rec.y + paddleHeight / 2) - 20;
	Rectangle arrowLP2;
	arrowLP2.width = 20;
	arrowLP2.height = 40;
	arrowLP2.x = paddle2.rec.x - 40;
	arrowLP2.y = (paddle1.rec.y + paddleHeight / 2) - 20;
	Rectangle arrowRP2;
	arrowRP2.width = 20;
	arrowRP2.height = 40;
	arrowRP2.x = paddle2.rec.x + paddle2.rec.width + 20;
	arrowRP2.y = (paddle2.rec.y + paddleHeight / 2) - 20;

	int randomN = GetRandomValue(1, 2);
	int point = randomN;

	bool enterPressed = false;

	randomN = GetRandomValue(1, 2);
	if (randomN == 1)
		ball.up = true;
	else
		ball.up = false;

	if (point % 2 == 0)
		ball.right = true;
	else
		ball.right = false;

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		BeginDrawing();

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
				paddle1.rec.y = (float)(screenHeight / 2 - paddleHeight / 2);
				paddle2.rec.y = (float)(screenHeight / 2 - paddleHeight / 2);
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
						if (paddle1Color > 0)
							paddle1Color--;
						else
							paddle1Color = 6;
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
						if (paddle1Color < 6)
							paddle1Color++;
						else
							paddle1Color = 0;
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
						if (paddle2Color > 0)
							paddle2Color--;
						else
							paddle2Color = 6;
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
						if (paddle2Color < 6)
							paddle2Color++;
						else
							paddle2Color = 0;
					}

					switch (paddle1Color)
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

					switch (paddle2Color)
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

			case GameState::PvP:
			{
				while (!WindowShouldClose() && currentState == GameState::PvP && (paddle1.score < 21 && paddle2.score < 21))
				{
					//Input
					//----------------------------------------------------------------------------------
					cursor = GetMousePosition();

					//Pausa
					if ((cursor.x > volverAndPausaButton.x && cursor.x < volverAndPausaButton.x + volverAndPausaButton.width)
						&&
						(cursor.y > volverAndPausaButton.y && cursor.y < volverAndPausaButton.y + volverAndPausaButton.height))
					{
						DrawRectangle((int)volverAndPausaButton.x, (int)volverAndPausaButton.y, (int)volverAndPausaButton.width, (int)volverAndPausaButton.height, RAYWHITE);
						DrawText("|| Pausa", (int)volverAndPausaButton.x + 5, (int)volverAndPausaButton.y + 5, 20, BLACK);
					}
					else
						DrawText("|| Pausa", (int)volverAndPausaButton.x + 5, (int)volverAndPausaButton.y + 5, 20, RAYWHITE);
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
						if (paddle1.rec.y < 0)
							paddle1.rec.y = 0;
						if (paddle1.rec.y + paddleHeight > screenHeight - 1)
							paddle1.rec.y = (screenHeight - 1) - paddleHeight;
						if (paddle2.rec.y < 0)
							paddle2.rec.y = 0;
						if (paddle2.rec.y + paddleHeight > screenHeight - 1)
							paddle2.rec.y = (screenHeight - 1) - paddleHeight;

						//Límites en y de la pelota
						if (ball.position.y - ball.radius <= 0)
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
							ball.direction = { (float)GetRandomValue(minBallSpeed, maxBallSpeed - 1), (float)(maxBallSpeed - ball.direction.x) };

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
						if (CheckCollisionCircleRec({ ball.position.x, ball.position.y }, (float)ball.radius, paddle1.rec))
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
						if (CheckCollisionCircleRec({ ball.position.x, ball.position.y }, (float)ball.radius, paddle2.rec))
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
						//----------------------------------------------------------------------------------
					}

					// Draw
					//----------------------------------------------------------------------------------
					DrawText("Objetivo: 21 pts.", screenWidth / 2 - 50, 10, 20, RAYWHITE);
					DrawText(TextFormat("%i", paddle1.score), 10, 40, 50, RAYWHITE);
					DrawText(TextFormat("%i", paddle2.score), screenWidth - 50, 40, 50, RAYWHITE);

					DrawRectangleV({paddle1.rec.x, paddle1.rec.y}, {paddleWidth, paddleHeight}, paddle1.color);
					DrawRectangleV({paddle2.rec.x, paddle2.rec.y}, {paddleWidth, paddleHeight}, paddle2.color);

					DrawCircleV(ball.position, (float)ball.radius, ball.color);

					if (pauseMenuActive)
					{
						DrawRectangle(pauseMenu.x, pauseMenu.y, pauseMenu.width, pauseMenu.height, BLACK);
						DrawRectangleLines(pauseMenu.x, pauseMenu.y, pauseMenu.width, pauseMenu.height, RAYWHITE);

						//Continuar
						if ((cursor.x > continuarButton.x && cursor.x < continuarButton.x + continuarButton.width)
							&&
							(cursor.y > continuarButton.y && cursor.y < continuarButton.y + continuarButton.height))
						{
							DrawRectangle((int)continuarButton.x, (int)continuarButton.y, (int)continuarButton.width, (int)continuarButton.height, RAYWHITE);
							DrawText("Continuar", (int)continuarButton.x + 5, (int)continuarButton.y + 5, 20, BLACK);
						}
						else
							DrawText("Continuar", (int)continuarButton.x + 5, (int)continuarButton.y + 5, 20, RAYWHITE);
						if (((cursor.x > continuarButton.x && cursor.x < continuarButton.x + continuarButton.width)
							&&
							(cursor.y > continuarButton.y && cursor.y < continuarButton.y + continuarButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
							pauseMenuActive = false;

						//Volver al menú de selección
						if ((cursor.x > volverAlMdSButton.x && cursor.x < volverAlMdSButton.x + volverAlMdSButton.width)
							&&
							(cursor.y > volverAlMdSButton.y && cursor.y < volverAlMdSButton.y + volverAlMdSButton.height))
						{
							DrawRectangle((int)volverAlMdSButton.x, (int)volverAlMdSButton.y, (int)volverAlMdSButton.width, (int)volverAlMdSButton.height, RAYWHITE);
							DrawText("Volver al menu de seleccion", (int)volverAlMdSButton.x + 5, (int)volverAlMdSButton.y + 5, 20, BLACK);
						}
						else
							DrawText("Volver al menu de seleccion", (int)volverAlMdSButton.x + 5, (int)volverAlMdSButton.y + 5, 20, RAYWHITE);
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
					}

					EndDrawing();
					ClearBackground(BLACK);
					//----------------------------------------------------------------------------------
				}

				paddle1.score = 0;
				paddle2.score = 0;
				currentState = GameState::GameOver;

				break;
			}

			case GameState::PvIA:
			{
				while (!WindowShouldClose() && currentState == GameState::PvIA && (paddle1.score < 21 && paddle2.score < 21))
				{
					//Input
					//----------------------------------------------------------------------------------
					cursor = GetMousePosition();

					//Pausa
					if ((cursor.x > volverAndPausaButton.x && cursor.x < volverAndPausaButton.x + volverAndPausaButton.width)
						&&
						(cursor.y > volverAndPausaButton.y && cursor.y < volverAndPausaButton.y + volverAndPausaButton.height))
					{
						DrawRectangle((int)volverAndPausaButton.x, (int)volverAndPausaButton.y, (int)volverAndPausaButton.width, (int)volverAndPausaButton.height, RAYWHITE);
						DrawText("|| Pausa", (int)volverAndPausaButton.x + 5, (int)volverAndPausaButton.y + 5, 20, BLACK);
					}
					else
						DrawText("|| Pausa", (int)volverAndPausaButton.x + 5, (int)volverAndPausaButton.y + 5, 20, RAYWHITE);
					if (((cursor.x > volverAndPausaButton.x && cursor.x < volverAndPausaButton.x + volverAndPausaButton.width)
						&&
						(cursor.y > volverAndPausaButton.y && cursor.y < volverAndPausaButton.y + volverAndPausaButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
						pauseMenuActive = true;

					if (!pauseMenuActive)
					{
						//Input del jugador
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
						//----------------------------------------------------------------------------------

						// Update
						//----------------------------------------------------------------------------------
						//Movimiento de la IA
						if (ball.position.x > (screenWidth - 1) / 2)
						{
							if (ball.up)
							{
								if (paddle2.rec.y > ball.position.y)
									paddle2.rec.y -= IAPaddleSpeed;
							}
							else
							{
								if (paddle2.rec.y < ball.position.y)
									paddle2.rec.y += IAPaddleSpeed;
							}
						}

						//Límites de las paletas
						if (paddle1.rec.y < 0)
							paddle1.rec.y = 0;
						if (paddle1.rec.y + paddleHeight > screenHeight - 1)
							paddle1.rec.y = (screenHeight - 1) - paddleHeight;
						if (paddle2.rec.y < 0)
							paddle2.rec.y = 0;
						if (paddle2.rec.y + paddleHeight > screenHeight - 1)
							paddle2.rec.y = (screenHeight - 1) - paddleHeight;

						//Límites en y de la pelota
						if (ball.position.y - ball.radius <= 0)
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
							ball.direction = { (float)GetRandomValue(minBallSpeed, maxBallSpeed - 1), (float)(maxBallSpeed - ball.direction.x) };
							IAPaddleSpeed = (float)GetRandomValue((int)minIAPaddleSpeed, (int)maxIAPaddleSpeed);

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
						if (CheckCollisionCircleRec({ ball.position.x, ball.position.y }, (float)ball.radius, paddle1.rec))
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
						if (CheckCollisionCircleRec({ ball.position.x, ball.position.y }, (float)ball.radius, paddle2.rec))
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
						//----------------------------------------------------------------------------------
					}

					// Draw
					//----------------------------------------------------------------------------------
					DrawText("Objetivo: 21 pts.", screenWidth / 2 - 50, 10, 20, RAYWHITE);
					DrawText(TextFormat("%i", paddle1.score), 10, 40, 50, RAYWHITE);
					DrawText(TextFormat("%i", paddle2.score), screenWidth - 50, 40, 50, RAYWHITE);

					DrawRectangleV({ paddle1.rec.x, paddle1.rec.y }, { paddleWidth, paddleHeight }, paddle1.color);
					DrawRectangleV({ paddle2.rec.x, paddle2.rec.y }, { paddleWidth, paddleHeight }, paddle2.color);

					DrawCircleV(ball.position, (float)ball.radius, ball.color);

					if (pauseMenuActive)
					{
						DrawRectangle(pauseMenu.x, pauseMenu.y, pauseMenu.width, pauseMenu.height, BLACK);
						DrawRectangleLines(pauseMenu.x, pauseMenu.y, pauseMenu.width, pauseMenu.height, RAYWHITE);

						//Continuar
						if ((cursor.x > continuarButton.x && cursor.x < continuarButton.x + continuarButton.width)
							&&
							(cursor.y > continuarButton.y && cursor.y < continuarButton.y + continuarButton.height))
						{
							DrawRectangle((int)continuarButton.x, (int)continuarButton.y, (int)continuarButton.width, (int)continuarButton.height, RAYWHITE);
							DrawText("Continuar", (int)continuarButton.x + 5, (int)continuarButton.y + 5, 20, BLACK);
						}
						else
							DrawText("Continuar", (int)continuarButton.x + 5, (int)continuarButton.y + 5, 20, RAYWHITE);
						if (((cursor.x > continuarButton.x && cursor.x < continuarButton.x + continuarButton.width)
							&&
							(cursor.y > continuarButton.y && cursor.y < continuarButton.y + continuarButton.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
							pauseMenuActive = false;

						//Volver al menú de selección
						if ((cursor.x > volverAlMdSButton.x && cursor.x < volverAlMdSButton.x + volverAlMdSButton.width)
							&&
							(cursor.y > volverAlMdSButton.y && cursor.y < volverAlMdSButton.y + volverAlMdSButton.height))
						{
							DrawRectangle((int)volverAlMdSButton.x, (int)volverAlMdSButton.y, (int)volverAlMdSButton.width, (int)volverAlMdSButton.height, RAYWHITE);
							DrawText("Volver al menu de seleccion", (int)volverAlMdSButton.x + 5, (int)volverAlMdSButton.y + 5, 20, BLACK);
						}
						else
							DrawText("Volver al menu de seleccion", (int)volverAlMdSButton.x + 5, (int)volverAlMdSButton.y + 5, 20, RAYWHITE);
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
					}

					EndDrawing();
					ClearBackground(BLACK);
					//----------------------------------------------------------------------------------
				}

				paddle1.score = 0;
				paddle2.score = 0;

				if (paddle1.score == 21 && paddle2.score == 21)
					currentState = GameState::GameOver;
				break;
			}

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

		EndDrawing();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();           // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}