#include <iostream>

#include "entity.h"
#include "game.h"
#include "misc.h"
#include "input.h"
#include "sector.h"

cGame::cGame() {
	// Build player	
}

void cGame::Update(cInput *i) {
	if(i->windowExit) { this->Quit(); return;}

	switch(i->currentInput) {
		case FORWARD:
			this->player.ThrustForward();
			this->player.velocity.z = Misc::DecayTo(this->player.velocity.z, 0, .01);
			break;
		case LEFT:
			this->player.Slow();
			this->player.velocity.z = Misc::DecayTo(this->player.velocity.z, this->player.rotationSpeed, .01);
			break;
		case FORLEFT:
			this->player.velocity.z = Misc::DecayTo(this->player.velocity.z, this->player.rotationSpeed, .01);
			this->player.ThrustForward();
			break;
		case RIGHT:
			this->player.Slow();
			this->player.velocity.z = Misc::DecayTo(this->player.velocity.z, -(this->player.rotationSpeed), .01);
			break;
		case FORRIGHT:
			this->player.velocity.z = Misc::DecayTo(this->player.velocity.z, -(this->player.rotationSpeed), .01);
			this->player.ThrustForward();
			break;
		default:
			std::cout << "INPUT TYPE UNHANDLED" << std::endl;
		case NONE:
			this->player.Slow();
			this->player.velocity.z = Misc::DecayTo(this->player.velocity.z, 0, .01);
			break;
	}
}

void cGame::Quit() {
	this->running = false;
}
