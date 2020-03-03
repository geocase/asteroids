#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include "input.h"

class cGame;

class cGame {
public:
	cEntity player;

	bool running = true;

	void Quit();
	void Update(cInput *i); 

	cGame();
};

#endif
