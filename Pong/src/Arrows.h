#ifndef ARROWS_H
#define ARROWSS_H

#include "raylib.h"

struct Arrow
{
	Vector2 v1;
	Vector2 v2;
	Vector2 v3;
};

extern Arrow leftPaddle1;
extern Arrow leftPaddle2;
extern Arrow rightPaddle1;
extern Arrow rightPaddle2;

#endif