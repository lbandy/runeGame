#ifndef RUNE_H
#define RUNE_H

class Rune
{
	int index;
	int value;

	SDL_Rect movingPosition;

	float targetPosX;
	float targetPosY;
	int steps;
};

#endif