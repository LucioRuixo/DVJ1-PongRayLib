#include "selection_menu.h"

#include "Game/game.h"
#include "Game/Elements/arrows.h"
#include "Game/Elements/buttons.h"
#include "Game/Elements/paddles.h"

namespace Selection_Menu
{
static void Init();
static void Update();
static void Draw();
static void SetPaddleColor(Paddle &paddle);

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
	InitArrows(paddle1);

	paddle2 = InitPaddle();
	paddle2.rec.x = screenWidth / 20 * 19 - paddleWidth;
	InitArrows(paddle2);
}

static void Update()
{
	cursor = GetMousePosition();

	GenerateButton(volver);

	GenerateButton(jugar);

	GeneratePaddleArrows(paddle1);
	GeneratePaddleArrows(paddle2);

	SetPaddleColor(paddle1);
	SetPaddleColor(paddle2);
}

static void Draw()
{
	DrawText("Seleccionen el color de las paletas.", screenWidth / 2 - 175, screenHeight / 2 - 45, 20, RAYWHITE);

	//Paletas
	DrawRectangleV({ paddle1.rec.x, paddle1.rec.y }, { paddleWidth, paddleHeight }, paddle1.color);
	DrawRectangleV({ paddle2.rec.x, paddle2.rec.y }, { paddleWidth, paddleHeight }, paddle2.color);
}

static void SetPaddleColor(Paddle &paddle)
{
	switch (paddle.colorCode)
	{
	case 0:
		paddle.color = RAYWHITE;
		break;
	case 1:
		paddle.color = RED;
		break;
	case 2:
		paddle.color = BLUE;
		break;
	case 3:
		paddle.color = YELLOW;
		break;
	case 4:
		paddle.color = GREEN;
		break;
	case 5:
		paddle.color = ORANGE;
		break;
	case 6:
		paddle.color = PURPLE;
		break;
	}
}
}