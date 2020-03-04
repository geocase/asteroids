#ifndef ENTITY_H
#define ENTITY_H

#include "sector.h"

class cEntity;
class cEntityPlayer;
class cEntityAsteroid;

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

class cEntityAsteroid : public cEntity {
public:
	cEntityAsteroid();
	void GenerateRandomShape(uint32_t min, uint32_t max);
};
#endif
