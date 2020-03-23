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
	if(i->windowExit) { this->Quit(); return;}

	switch(i->currentInput) {
		case FORWARD:
			this->player.ThrustForward();
			this->player.velocity.z = 0; 
			break;
		case LEFT:
			this->player.velocity.x = 0;
			this->player.velocity.y = 0;
			this->player.velocity.z = this->player.rotationSpeed;
			break;
		case FORLEFT:
			this->player.velocity.z = this->player.rotationSpeed;
			this->player.ThrustForward();
			break;
		case RIGHT:
			this->player.velocity.x = 0;
			this->player.velocity.y = 0;
			this->player.velocity.z = -(this->player.rotationSpeed);
			break;
		case FORRIGHT:
			this->player.velocity.z = -(this->player.rotationSpeed);
			this->player.ThrustForward();
			break;
		default:
			std::cout << "INPUT TYPE UNHANDLED" << std::endl;
		case NONE:
			this->player.velocity.x = 0;
			this->player.velocity.y = 0;
			this->player.velocity.z = 0;
			break;

	}
}

void cGame::Quit() {
	this->running = false;
}
