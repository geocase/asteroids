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
