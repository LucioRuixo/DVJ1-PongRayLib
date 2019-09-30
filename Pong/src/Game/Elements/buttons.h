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

extern Button continuar;
extern Button jugadorVsJugador;
extern Button jugadorVsIA;
extern Button jugar;
extern Button pantallaCompleta;
extern Button pausa;
extern Button pauseMenu;
extern Button salir;
extern Button volver;
extern Button volverAlMenuDeSeleccion;
extern Button volverAlMenuPrincipal;

//----------------------------------------------------------------

void GenerateButton(Button button);

void InitMainMenuButtons(Button &jugadorVsIA, Button &jugadorVsJugador, Button &pantallaCompleta, Button &salir);
void InitSelectionMenuButtons(Button &jugar, Button &volver);
void InitGameplayAndGameOverButtons(Button &continuar, Button &pausa, Button &pauseMenu, Button &volverAlMenuDeSeleccion, Button &volverAlMenuPrincipal);

#endif