#include <iostream>

#include "entity.h"
#include "sector.h"

void cEntity::PlaceAt(const double x, const double y) {	
	double yDiff = 0;
	double xDiff = 0;
	for(int i = 0; i < this->nodeCount; i++) {
		yDiff = this->nodes[i].y - this->yPos;
		xDiff = this->nodes[i].x - this->xPos;
		this->nodes[i].PlaceAt(x + xDiff, y + yDiff);
	}

	this->xPos = x;
	this->yPos = y;

}

void cEntity::Rotate(const double r) {
	this->angle += r;
	this->shape.Rotate(this->xPos, this->yPos, r);
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
	this->xPos = 100;
	this->yPos = 100;
	this->GenerateRandomShape(pow(this->size - 1, 2), pow(this->size, 2));
}

void cEntityAsteroid::GenerateRandomShape(uint32_t min, uint32_t max) {
	if(!this->shapeGenerated) {
		this->nodeCount = 10;
		this->nodes = new cVertex[nodeCount];
	}
	for(int i = 0; i < nodeCount; i++) {
		this->nodes[i].PlaceAt(this->xPos + (min + rand() % max), yPos);
		this->nodes[i].Rotate(this->xPos, this->yPos, .62831853071 * i);
	}
	if(!this->shapeGenerated) {
		this->shape.BuildFromVertexArray(this->nodes, this->nodeCount);
	}
	this->shapeGenerated = true;
}

void cEntityAsteroid::SetSize(const uint32_t s) {
	if(s <= this->minimumSize){
		this->dead = true;
		return;
	}

	this->size = s;
	this->GenerateRandomShape(pow(this->size - 1, 2), pow(this->size, 2));
}
