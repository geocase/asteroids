#include <iostream>

#include "entity.h"
#include "sector.h"

void cEntity::Rotate(const double r) {
	this->angle += r;
	for(int i = 0; i < this->nodeCount; i++) {
		this->nodes[i].Rotate(this->xPos, this->yPos, r);
	}
}

void cEntity::Translate(double x, double y) {
	this->xPos += x;
	this->yPos += y;
	for(int i = 0; i < this->nodeCount; i++) {
		this->nodes[i].x += x;
		this->nodes[i].y += y;		
	}
}

cEntityPlayer::cEntityPlayer() {
	this->nodeCount = 4;
	this->nodes = new cVertex[this->nodeCount];
	this->xPos = 160;
	this->yPos = 100;
	this->angle = 0;

	this->nodes[0].PlaceAt(this->xPos + this->shipScale, this->yPos);
	this->nodes[1].PlaceAt(this->xPos + this->shipScale, this->yPos);
	this->nodes[1].Rotate(this->xPos, this->yPos, 2.35619);
	this->nodes[2].PlaceAt(this->xPos - this->shipScale / 2, this->yPos);
	this->nodes[3].PlaceAt(this->xPos + this->shipScale, this->yPos);
	this->nodes[3].Rotate(this->xPos, this->yPos, -2.35619);

	this->shape.BuildFromVertexArray(this->nodes, 4);
}

cEntityAsteroid::cEntityAsteroid() {
	this->GenerateRandom(10, 5);
}

void cEntityAsteroid::GenerateRandom(uint32_t min, uint32_t max) {

}
