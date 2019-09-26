#ifndef BUTTONS_H
#define BUTTONS_H

#include "raylib.h"

extern Rectangle pantallaCompletaButton;
extern Rectangle jVsJButton;
extern Rectangle jVsIAButton;
extern Rectangle salirButton;
extern Rectangle jugarButton;
extern Rectangle volverAndPausaButton;
extern Rectangle pauseMenu;
extern Rectangle continuarButton;
extern Rectangle volverAlMdSButton;
extern Rectangle volverAlMPButton;

extern Rectangle arrowLP1;
extern Rectangle arrowRP1;
extern Rectangle arrowLP2;
extern Rectangle arrowRP2;

//----------------------------------------------------------------

void InitMainMenuButtons(Rectangle &pantallaCompletaButton, Rectangle &jVsJButton, Rectangle &jVsIAButton, Rectangle &salirButton);
void InitSelectionMenuButtons(Rectangle &jugarButton, Rectangle &volverAndPausaButton, Rectangle &arrowLP1, Rectangle &arrowRP1, Rectangle &arrowLP2, Rectangle &arrowRP2);
void InitGameplayButtons(Rectangle &jugarButton, Rectangle &volverAndPausaButton, Rectangle &pauseMenu, Rectangle &continuarButton, Rectangle &volverAlMdSButton, Rectangle &volverAlMPButton);
void InitGameOverButtons(Rectangle &volverAlMdSButton, Rectangle &volverAlMPButton);

#endif