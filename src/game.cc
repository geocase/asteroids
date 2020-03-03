#include <iostream>

#include "entity.h"
#include "game.h"
#include "input.h"
#include "sector.h"
#define SHIP_SCALE 20


cGame::cGame() {
	// Build player	
}

void cGame::Update(cInput *i) {
	if(i->windowExit) { this->Quit(); }
}

void cGame::Quit() {
	this->running = false;
}
