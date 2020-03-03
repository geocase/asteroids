#ifndef GAME_H
#define GAME_H

#include "input.h"

class cGame;

class cGame {
public:
	bool running = true;

	void Quit();
	void Update(cInput *i); 
};

#endif
