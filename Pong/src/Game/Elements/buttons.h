#ifndef BUTTONS_H
#define BUTTONS_H

#include "raylib.h"

#include "Game/game.h"

enum Function
{
	ChangeState,
	ExitGame,
	Fullscreen,
	Pause,
	Play,
	SelectPvAI,
	SelectPvP
};

struct Button
{
	Function function;

	GameState state;
	Rectangle rec;

	const char* text;
};

extern Button continue_;
extern Button playerVsPlayer;
extern Button jugadorVsIA;
extern Button jugar;
extern Button fullScreen_;
extern Button pause;
extern Button pauseMenu;
extern Button exit;
extern Button return_;
extern Button returnToSelectionMenu;
extern Button returnToMainMenu;

//----------------------------------------------------------------

void GenerateButton(Button button);

void InitMainMenuButtons(Button &jugadorVsIA, Button &playerVsPlayer, Button &fullScreen_, Button &exit);
void InitSelectionMenuButtons(Button &jugar, Button &return_);
void InitGameplayAndGameOverButtons(Button &continue_, Button &pause, Button &pauseMenu, Button &returnToSelectionMenu, Button &returnToMainMenu);

#endif