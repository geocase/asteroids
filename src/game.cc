#include <iostream>

#include "game.h"
#include "input.h"
#include "sector.h"
#define SHIP_SCALE 20

cGame::cGame() {
	// Build player
	this->player.nodes = new cVertex[4];
	this->player.xPos = 160;
	this->player.yPos = 100;

	this->player.nodes[0].PlaceAt(this->player.xPos + SHIP_SCALE, this->player.yPos);
	this->player.nodes[1].PlaceAt(this->player.xPos + SHIP_SCALE, this->player.yPos);
	this->player.nodes[1].Rotate(this->player.xPos, this->player.yPos, 2.35619);
	this->player.nodes[2].PlaceAt(this->player.xPos - SHIP_SCALE / 2, this->player.yPos);
	this->player.nodes[3].PlaceAt(this->player.xPos + SHIP_SCALE, this->player.yPos);
	this->player.nodes[3].Rotate(this->player.xPos, this->player.yPos, -2.35619);

	this->player.shape.BuildFromVertexArray(this->player.nodes, 4);
}

void cGame::Update(cInput *i) {
	if(i->windowExit) { this->Quit(); }
}

void cGame::Quit() {
	this->running = false;
}
