#include "Selection Menu.h"

#include "Game.h"
#include "Buttons.h"
#include "Paddles.h"

namespace Selection_Menu
{
static void Init();
static void Update();
static void Draw();

void Execute()
{
	Init();

	while (!WindowShouldClose() && currentState == GameState::SelectionMenu)
	{
		ClearBackground(BLACK);
		
		Update();

		Draw();

		EndDrawing();
	}
}

static void Init()
{
	paddle1 = InitPaddle();
	paddle1.rec.x = screenWidth / 20;
	paddle2 = InitPaddle();
	paddle2.rec.x = screenWidth / 20 * 19 - paddleWidth;
}

static void Update()
{
	cursor = GetMousePosition();

	GenerateButton(volver);

	GenerateButton(jugar);
	/*
	//Flechas
	if (((cursor.x > arrowLP1.x && cursor.x < arrowLP1.x + arrowLP1.width)
		&&
		(cursor.y > arrowLP1.y && cursor.y < arrowLP1.y + arrowLP1.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (paddle1.colorCode > 0)
			paddle1.colorCode--;
		else
			paddle1.colorCode = 6;
	}

	if (((cursor.x > arrowRP1.x && cursor.x < arrowRP1.x + arrowRP1.width)
		&&
		(cursor.y > arrowRP1.y && cursor.y < arrowRP1.y + arrowRP1.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (paddle1.colorCode < 6)
			paddle1.colorCode++;
		else
			paddle1.colorCode = 0;
	}

	if (((cursor.x > arrowLP2.x && cursor.x < arrowLP2.x + arrowLP2.width)
		&&
		(cursor.y > arrowLP2.y && cursor.y < arrowLP2.y + arrowLP2.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (paddle2.colorCode > 0)
			paddle2.colorCode--;
		else
			paddle2.colorCode = 6;
	}

	if (((cursor.x > arrowRP2.x && cursor.x < arrowRP2.x + arrowRP2.width)
		&&
		(cursor.y > arrowRP2.y && cursor.y < arrowRP2.y + arrowRP2.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (paddle2.colorCode < 6)
			paddle2.colorCode++;
		else
			paddle2.colorCode = 0;
	}*/

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
}

static void Draw()
{
	DrawText("Seleccionen el color de las paletas.", screenWidth / 2 - 175, screenHeight / 2 - 45, 20, RAYWHITE);

	//Paletas
	DrawRectangleV({ paddle1.rec.x, paddle1.rec.y }, { paddleWidth, paddleHeight }, paddle1.color);
	DrawRectangleV({ paddle2.rec.x, paddle2.rec.y }, { paddleWidth, paddleHeight }, paddle2.color);

	//Flechas
	DrawTriangle(
		{ paddle1.rec.x - 20, paddle1.rec.y + paddleHeight / 2 - 20 },
		{ paddle1.rec.x - 40, paddle1.rec.y + paddleHeight / 2 },
		{ paddle1.rec.x - 20, paddle1.rec.y + paddleHeight / 2 + 20 },
		RAYWHITE);

	DrawTriangle(
		{ paddle1.rec.x + paddleWidth + 40, paddle1.rec.y + paddleHeight / 2 },
		{ paddle1.rec.x + paddleWidth + 20, paddle1.rec.y + paddleHeight / 2 - 20 },
		{ paddle1.rec.x + paddleWidth + 20, paddle1.rec.y + paddleHeight / 2 + 20 },
		RAYWHITE);

	DrawTriangle(
		{ paddle2.rec.x - 20, paddle2.rec.y + paddleHeight / 2 - 20 },
		{ paddle2.rec.x - 40, paddle2.rec.y + paddleHeight / 2 },
		{ paddle2.rec.x - 20, paddle2.rec.y + paddleHeight / 2 + 20 },
		RAYWHITE);

	DrawTriangle(
		{ paddle2.rec.x + paddleWidth + 40, paddle2.rec.y + paddleHeight / 2 },
		{ paddle2.rec.x + paddleWidth + 20, paddle2.rec.y + paddleHeight / 2 - 20 },
		{ paddle2.rec.x + paddleWidth + 20, paddle2.rec.y + paddleHeight / 2 + 20 },
		RAYWHITE);
}
}