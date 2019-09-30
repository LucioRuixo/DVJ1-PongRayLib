#include "buttons.h"

#include "Game/States/gameplay.h"
#include "Game/Elements/paddles.h"

Button continuar;
Button jugadorVsJugador;
Button jugadorVsIA;
Button jugar;
Button pantallaCompleta;
Button pausa;
Button pauseMenu;
Button salir;
Button volver;
Button volverAlMenuDeSeleccion;
Button volverAlMenuPrincipal;

//----------------------------------------------------------------

void GenerateButton(Button button)
{
	if ((cursor.x > button.rec.x && cursor.x < button.rec.x + button.rec.width)
		&&
		(cursor.y > button.rec.y && cursor.y < button.rec.y + button.rec.height))
	{
		DrawRectangle(static_cast<int>(button.rec.x), static_cast<int>(button.rec.y), static_cast<int>(button.rec.width), static_cast<int>(button.rec.height), RAYWHITE);
		DrawText(button.text, static_cast<int>(button.rec.x + 5), static_cast<int>(button.rec.y + 5), 20, BLACK);
	}
	else
		DrawText(button.text, static_cast<int>(button.rec.x + 5), static_cast<int>(button.rec.y + 5), 20, RAYWHITE);
	if (((cursor.x > button.rec.x && cursor.x < button.rec.x + button.rec.width)
		&&
		(cursor.y > button.rec.y && cursor.y < button.rec.y + button.rec.height)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		switch (button.function)
		{
		case Function::ChangeState:
			currentState = button.state;
			break;
		case Function::ExitGame:
			CloseWindow();
			break;
		case Function::Pause:
			pauseState ? pauseState = false : pauseState = true;
			break;
		case Function::Play:
			currentState = selectedGameMode;
			break;
		case Function::SelectPvAI:
			selectedGameMode = GameState::PvAI;
			currentState = button.state;
			break;
		case Function::SelectPvP:
			selectedGameMode = GameState::PvP;
			currentState = button.state;
			break;
		case Function::Fullscreen:
			ToggleFullscreen();
			break;
		}
	}
}

//Init
void InitMainMenuButtons(Button &jugadorVsIA, Button &jugadorVsJugador, Button &pantallaCompleta, Button &salir)
{
	jugadorVsIA.function = Function::SelectPvAI;
	jugadorVsIA.state = GameState::SelectionMenu;
	jugadorVsIA.rec.width = 160;
	jugadorVsIA.rec.height = 30;
	jugadorVsIA.rec.x = screenWidth / 2 - 70;
	jugadorVsIA.rec.y = screenHeight / 2 + 80;
	jugadorVsIA.text = "Jugador vs. IA";

	jugadorVsJugador.function = Function::SelectPvP;
	jugadorVsJugador.state = GameState::SelectionMenu;
	jugadorVsJugador.rec.width = 220;
	jugadorVsJugador.rec.height = 30;
	jugadorVsJugador.rec.x = screenWidth / 2 - 100;
	jugadorVsJugador.rec.y = screenHeight / 2 + 45;
	jugadorVsJugador.text = "Jugador vs. Jugador";

	pantallaCompleta.function = Function::Fullscreen;
	pantallaCompleta.rec.width = 190;
	pantallaCompleta.rec.height = 30;
	pantallaCompleta.rec.x = screenWidth - pantallaCompleta.rec.width - 10;
	pantallaCompleta.rec.y = 10;
	pantallaCompleta.text = "Pantalla completa";

	salir.function = Function::ExitGame;
	salir.rec.width = 60;
	salir.rec.height = 30;
	salir.rec.x = screenWidth / 2 - 20;
	salir.rec.y = screenHeight / 2 + 115;
	salir.text = "Salir";
}

void InitSelectionMenuButtons(Button &jugar, Button &volver)
{
	jugar.function = Function::Play;
	jugar.rec.width = 80;
	jugar.rec.height = 30;
	jugar.rec.x = screenWidth / 2 - 35;
	jugar.rec.y = screenHeight / 2 + 45;
	jugar.text = "JUGAR";

	volver.function = Function::ChangeState;
	volver.state = GameState::MainMenu;
	volver.rec.width = 95;
	volver.rec.height = 30;
	volver.rec.x = 10;
	volver.rec.y = 10;
	volver.text = "< Volver";
}

void InitGameplayAndGameOverButtons(Button &continuar, Button &pausa, Button &pauseMenu, Button &volverAlMenuDeSeleccion, Button &volverAlMenuPrincipal)
{
	pauseMenu.rec.width = 315;
	pauseMenu.rec.height = 130;
	pauseMenu.rec.x = screenWidth / 2 - pauseMenu.rec.width / 2;
	pauseMenu.rec.y = screenHeight / 2 - pauseMenu.rec.height / 2;

	continuar.function = Function::Pause;
	continuar.rec.width = 110;
	continuar.rec.height = 30;
	continuar.rec.x = screenWidth / 2 - continuar.rec.width / 2;
	continuar.rec.y = screenHeight / 2 - continuar.rec.height / 2 - ((pauseMenu.rec.height - continuar.rec.height * 3) / 4 + continuar.rec.height);
	continuar.text = "Continuar";

	pausa.function = Function::Pause;
	pausa.rec.width = 95;
	pausa.rec.height = 30;
	pausa.rec.x = 10;
	pausa.rec.y = 10;
	pausa.text = "|| Pausa";

	volverAlMenuDeSeleccion.function = Function::ChangeState;
	volverAlMenuDeSeleccion.state = GameState::SelectionMenu;
	volverAlMenuDeSeleccion.rec.width = 295;
	volverAlMenuDeSeleccion.rec.height = 30;
	volverAlMenuDeSeleccion.rec.x = screenWidth / 2 - volverAlMenuDeSeleccion.rec.width / 2;
	volverAlMenuDeSeleccion.rec.y = screenHeight / 2 - volverAlMenuDeSeleccion.rec.height / 2;
	volverAlMenuDeSeleccion.text = "Volver al menu de seleccion";

	volverAlMenuPrincipal.function = Function::ChangeState;
	volverAlMenuPrincipal.state = GameState::MainMenu;
	volverAlMenuPrincipal.rec.width = 255;
	volverAlMenuPrincipal.rec.height = 30;
	volverAlMenuPrincipal.rec.x = screenWidth / 2 - volverAlMenuPrincipal.rec.width / 2;
	volverAlMenuPrincipal.rec.y = screenHeight / 2 - volverAlMenuPrincipal.rec.height / 2 + ((pauseMenu.rec.height - volverAlMenuPrincipal.rec.height * 3) / 4 + volverAlMenuPrincipal.rec.height);
	volverAlMenuPrincipal.text = "Volver al menu principal";
}