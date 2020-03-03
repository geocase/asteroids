#include <iostream>

#include "game.h"
#include "input.h"


void cGame::Update(cInput *i) {
	if(i->windowExit) { this->Quit(); }
}

void cGame::Quit() {
	this->running = false;
}
