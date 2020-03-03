#include <iostream>

#include "game.h"
#include "input.h"
#include "sector.h"
#define SHIP_SCALE 20


void cEntity::Translate(double x, double y) {
	this->xPos += x;
	this->yPos += y;
	for(int i = 0; i < this->nodeCount; i++) {
		this->nodes[i].x += x;
		this->nodes[i].y += y;
		
	}
}

cGame::cGame() {
	// Build player	
	this->player.nodeCount = 4;
	this->player.nodes = new cVertex[this->player.nodeCount];
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
