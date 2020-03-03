#include <iostream>
#include <cmath>
#include "sector.h"

void cVertex::Rotate(const double ax, const double ay, const double r) {
	double nx = (this->x - ax) * std::cos(r) - (this->y - ay) * std::sin(r);
	double ny = (this->y - ay) * std::cos(r) + (this->x - ax) * std::sin(r);

	this->PlaceAt(nx + ax, ny + ay);
}

void cVertex::PlaceAt(const double nx, const double ny) {
	this->x = nx;
	this->y = ny;
}

cSegment::cSegment(double ax, double ay, double bx, double by) {
	this->a->x = ax;
	this->a->y = ay;
	this->b->x = bx;
	this->b->y = by;
}

cSegment::cSegment(cVertex *na, cVertex *nb) {
	this->a = na;
	this->b = nb;
}

cVertex cSegment::GetPointAt(double ratio) {
	cVertex temp;
	temp.x = (this->a->x - this->b->x) * ratio + this->b->x;
	temp.y = (this->a->y - this->b->y) * ratio + this->b->y;

	return temp;
}

void cPolygon::AddFace(const cSegment *l) {
	this->faces.push_back(*l);	
	this->faceCount++;
}

void cPolygon::BuildFromVertexArray(cVertex *p, uint32_t nc) {
	for(int i = 0; i < nc; i++) {
		if(i + 1 > nc - 1) {
			this->AddFace(new cSegment(&p[i], &p[0]));
		} else {
			this->AddFace(new cSegment(&p[i], &p[i+1]));
		}
	}
}

void cPath::AddSegment(const cSegment *l) {
	this->lineDefs.push_back(*l);
	this->lineDefCount++;
}

void cPath::BuildFromVertexArray(cVertex *p, uint32_t nc) {
	for(int i = 0; i < nc - 1; i++) {
		this->AddSegment(new cSegment(&p[i], &p[i+1]));
	}
}
