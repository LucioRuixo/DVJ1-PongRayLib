#ifndef GAME_H
#define GAME_H

#include "raylib.h"

const int screenWidth = 1280;
const int screenHeight = 720;

enum GameState
{
	MainMenu,
	SelectionMenu,
	PvP,
	PvAI,
	GameOver
};

extern GameState currentState;
extern GameState selectedGameMode;

extern Vector2 cursor;

extern float deltaTime;

extern bool enterPressed;

//----------------------------------------------------------------
namespace Game_
{
void Execute();
}

#endif