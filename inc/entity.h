#ifndef ENTITY_H
#define ENTITY_H

#include "sector.h"

class cEntity;
class cEntityPlayer;

class cEntity {
public:
	cPolygon shape;
	cVertex *nodes;
	uint32_t nodeCount;

	double xPos, yPos;
	double angle;
	void Rotate(const double r);
	void Translate(double x, double y);
};

class cEntityPlayer : public cEntity {
public:
	uint32_t shipScale = 20;
	cEntityPlayer();
};
#endif
