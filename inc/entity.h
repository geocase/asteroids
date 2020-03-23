#ifndef ENTITY_H
#define ENTITY_H

#include "sector.h"
#include "misc.h"

class cEntity;
class cEntityPlayer;
class cEntityAsteroid;

class cEntity {
public:
	cPolygon shape;
	cVertex *nodes;
	uint32_t nodeCount;

	uint32_t speed;

	Misc::Vector3_t position; // Angle included, z
	Misc::Vector3_t velocity;

	void PlaceAt(const double x, const double y);
	void Rotate(const double r);
	void Translate(double x, double y);
	void ThrustForward();
	void Update(double time);
};

class cEntityPlayer : public cEntity {
public:
	uint32_t shipScale = 20;
	double rotationSpeed = 0.6;
	cEntityPlayer();
};

class cEntityAsteroid : public cEntity {
public:
	const uint32_t minimumSize = 4;
	const uint32_t maximumSize = 7;
	uint32_t size = maximumSize;
	bool dead = false;
	bool shapeGenerated = false;
	cEntityAsteroid();
	void GenerateRandomShape(uint32_t min, uint32_t max);
	void SetSize(const uint32_t s);
};
#endif
