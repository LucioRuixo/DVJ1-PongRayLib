#include "buttons.h"

#include "Game/game.h"
#include "Game/States/gameplay.h"
#include "Game/Elements/paddles.h"

Button continue_;
Button playerVsPlayer;
Button jugadorVsIA;
Button jugar;
Button fullScreen_;
Button pause;
Button pauseMenu;
Button exit;
Button return_;
Button returnToSelectionMenu;
Button returnToMainMenu;

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
			pauseActive ? pauseActive = false : pauseActive = true;
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
void InitMainMenuButtons(Button &jugadorVsIA, Button &playerVsPlayer, Button &fullScreen_, Button &exit)
{
	jugadorVsIA.function = Function::SelectPvAI;
	jugadorVsIA.state = GameState::SelectionMenu;
	jugadorVsIA.rec.width = 160;
	jugadorVsIA.rec.height = 30;
	jugadorVsIA.rec.x = screenWidth / 2 - 70;
	jugadorVsIA.rec.y = screenHeight / 2 + 80;
	jugadorVsIA.text = "Jugador vs. IA";

	playerVsPlayer.function = Function::SelectPvP;
	playerVsPlayer.state = GameState::SelectionMenu;
	playerVsPlayer.rec.width = 220;
	playerVsPlayer.rec.height = 30;
	playerVsPlayer.rec.x = screenWidth / 2 - 100;
	playerVsPlayer.rec.y = screenHeight / 2 + 45;
	playerVsPlayer.text = "Jugador vs. Jugador";

	fullScreen_.function = Function::Fullscreen;
	fullScreen_.rec.width = 190;
	fullScreen_.rec.height = 30;
	fullScreen_.rec.x = screenWidth - fullScreen_.rec.width - 10;
	fullScreen_.rec.y = 10;
	fullScreen_.text = "Pantalla completa";

	exit.function = Function::ExitGame;
	exit.rec.width = 60;
	exit.rec.height = 30;
	exit.rec.x = screenWidth / 2 - 20;
	exit.rec.y = screenHeight / 2 + 115;
	exit.text = "Salir";
}

void InitSelectionMenuButtons(Button &jugar, Button &return_)
{
	jugar.function = Function::Play;
	jugar.rec.width = 80;
	jugar.rec.height = 30;
	jugar.rec.x = screenWidth / 2 - 35;
	jugar.rec.y = screenHeight / 2 + 45;
	jugar.text = "JUGAR";

	return_.function = Function::ChangeState;
	return_.state = GameState::MainMenu;
	return_.rec.width = 95;
	return_.rec.height = 30;
	return_.rec.x = 10;
	return_.rec.y = 10;
	return_.text = "< Volver";
}

void InitGameplayAndGameOverButtons(Button &continue_, Button &pause, Button &pauseMenu, Button &return_AlMenuDeSeleccion, Button &return_AlMenuPrincipal)
{
	pauseMenu.rec.width = 315;
	pauseMenu.rec.height = 130;
	pauseMenu.rec.x = screenWidth / 2 - pauseMenu.rec.width / 2;
	pauseMenu.rec.y = screenHeight / 2 - pauseMenu.rec.height / 2;

	continue_.function = Function::Pause;
	continue_.rec.width = 110;
	continue_.rec.height = 30;
	continue_.rec.x = screenWidth / 2 - continue_.rec.width / 2;
	continue_.rec.y = screenHeight / 2 - continue_.rec.height / 2 - ((pauseMenu.rec.height - continue_.rec.height * 3) / 4 + continue_.rec.height);
	continue_.text = "Continuar";

	pause.function = Function::Pause;
	pause.rec.width = 95;
	pause.rec.height = 30;
	pause.rec.x = 10;
	pause.rec.y = 10;
	pause.text = "|| Pausa";

	returnToSelectionMenu.function = Function::ChangeState;
	returnToSelectionMenu.state = GameState::SelectionMenu;
	returnToSelectionMenu.rec.width = 295;
	returnToSelectionMenu.rec.height = 30;
	returnToSelectionMenu.rec.x = screenWidth / 2 - returnToSelectionMenu.rec.width / 2;
	returnToSelectionMenu.rec.y = screenHeight / 2 - returnToSelectionMenu.rec.height / 2;
	returnToSelectionMenu.text = "Volver al menu de seleccion";

	returnToMainMenu.function = Function::ChangeState;
	returnToMainMenu.state = GameState::MainMenu;
	returnToMainMenu.rec.width = 255;
	returnToMainMenu.rec.height = 30;
	returnToMainMenu.rec.x = screenWidth / 2 - returnToMainMenu.rec.width / 2;
	returnToMainMenu.rec.y = screenHeight / 2 - returnToMainMenu.rec.height / 2 + ((pauseMenu.rec.height - returnToMainMenu.rec.height * 3) / 4 + returnToMainMenu.rec.height);
	returnToMainMenu.text = "Volver al menu principal";
}