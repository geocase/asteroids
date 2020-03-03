#ifndef GAME_H
#define GAME_H

#include "input.h"
#include "sector.h"

class cGame;
class cEntity;

class cEntity {
public:
	cPolygon shape;
	cVertex *nodes;
	int32_t xPos, yPos;
	void Translate(double x, double y);
};

class cGame {
public:
	cEntity player;

	bool running = true;

	void Quit();
	void Update(cInput *i); 

	cGame();
};

#endif
