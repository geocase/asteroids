#include <iostream>
#include <cmath>

#include "entity.h"
#include "sector.h"

void cEntity::PlaceAt(const double x, const double y) {	
	double yDiff = 0;
	double xDiff = 0;
	for(uint32_t i = 0; i < this->nodeCount; i++) {
		yDiff = this->nodes[i].position.y - this->position.y;
		xDiff = this->nodes[i].position.x - this->position.x;
		this->nodes[i].PlaceAt(x + xDiff, y + yDiff);
	}

	this->position.x = x;
	this->position.y = y;

}

void cEntity::Rotate(const double r) {
	this->position.z += r;
	this->shape.Rotate(this->position.x, this->position.y, r / 2);
}

void cEntity::Translate(double x, double y) {
	this->position.x += x;
	this->position.y += y;
	for(uint32_t i = 0; i < this->nodeCount; i++) {
		this->nodes[i].position.x += x;
		this->nodes[i].position.y += y;
	}
}

void cEntity::ThrustForward() {
	this->velocity.y = sin(this->position.z) * this->speed;
	this->velocity.x = cos(this->position.z) * this->speed;
}

void cEntity::Update(double time) {
	this->Translate(this->velocity.x * time, this->velocity.y * time);
	this->Rotate(this->velocity.z * time);
}

cEntityPlayer::cEntityPlayer() {
	this->nodeCount = 4;
	this->nodes = new cVertex[this->nodeCount];
	this->position.x = 160;
	this->position.y = 100;
	this->position.z = 0;

	this->nodes[0].PlaceAt(this->position.x + this->shipScale, this->position.y);
	this->nodes[1].PlaceAt(this->position.x + this->shipScale, this->position.y);
	this->nodes[1].Rotate(this->position.x, this->position.y, 2.35619);
	this->nodes[2].PlaceAt(this->position.x - this->shipScale / 2, this->position.y);
	this->nodes[3].PlaceAt(this->position.x + this->shipScale, this->position.y);
	this->nodes[3].Rotate(this->position.x, this->position.y, -2.35619);

	this->shape.BuildFromVertexArray(this->nodes, 4);
}

cEntityAsteroid::cEntityAsteroid() {
	this->position.x = 100;
	this->position.y = 100;
	this->GenerateRandomShape(pow(this->size - 1, 2), pow(this->size, 2));
}

void cEntityAsteroid::GenerateRandomShape(uint32_t min, uint32_t max) {
	if(!this->shapeGenerated) {
		this->nodeCount = 10;
		this->nodes = new cVertex[nodeCount];
	}
	for(uint32_t i = 0; i < nodeCount; i++) {
		this->nodes[i].PlaceAt(this->position.x + (min + rand() % max), this->position.y);
		this->nodes[i].Rotate(this->position.x, this->position.y, .62831853071 * i);
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
