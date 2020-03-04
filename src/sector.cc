#include <iostream>
#include <cmath>
#include "sector.h"
#include "misc.h"

#include "window.h"

void cVertex::Rotate(const double ax, const double ay, const double r) {
	double nx = (this->x - ax) * std::cos(r) - (this->y - ay) * std::sin(r);
	double ny = (this->y - ay) * std::cos(r) + (this->x - ax) * std::sin(r);

	this->PlaceAt(nx + ax, ny + ay);
}

void cVertex::PlaceAt(const double nx, const double ny) {
	this->x = nx;
	this->y = ny;
}

bool cVertex::InPolygon(cPolygon *p, cWindow *w) {
	double yMin = p->faces.at(0).a->y, yMax = p->faces.at(0).a->y;
	double xMin = p->faces.at(0).a->x, xMax = p->faces.at(0).a->x;
	for(int i = 0; i < p->faceCount; i++) {
		if(p->faces.at(i).a->x < xMin) { xMin = p->faces.at(i).a->x;}
		if(p->faces.at(i).a->x > xMax) { xMax = p->faces.at(i).a->x;}
		if(p->faces.at(i).a->y < yMin) { yMin = p->faces.at(i).a->y;}
		if(p->faces.at(i).a->y > yMax) { yMax = p->faces.at(i).a->y;}
	}

	if(this->x < xMin || this->x > xMax || this->y < yMin || this->y > yMax) {
		return false;
	}

	sColor_t red;
	red.r = 255;
	red.b = 0;
	red.g = 0;
	red.a = 255;

	cVertex *endPoint = new cVertex;
	endPoint->PlaceAt(xMax, this->y);
	cSegment *testLine = new cSegment(this, endPoint);
	uint32_t colliderCount = 0;
	cVertex collisionPoint;

	for(int i = 0; i < p->faceCount; i++) {
		collisionPoint = testLine->GetIntersection(&(p->faces.at(i))); 
		std::cout << "\t" << this->x << ", " << this->y << ":" << endPoint->x << ", " << endPoint->y << std::endl;
		if((p->faces.at(i).a->y >= p->faces.at(i).b->y &&
		   collisionPoint.y >= p->faces.at(i).b->y && collisionPoint.y <= p->faces.at(i).a->y) ||
		   (p->faces.at(i).a->y <= p->faces.at(i).b->y && 
		   collisionPoint.y <= p->faces.at(i).b->y && collisionPoint.y >= p->faces.at(i).a->y)) {
	   		if(this->x <= collisionPoint.x) {
				w->DrawLine(450, 100, collisionPoint.x, collisionPoint.y, red);
				w->DrawLine(this->x, this->y, collisionPoint.x, collisionPoint.y, red);
				colliderCount++;
				std::cout << "COLLIDER ";
			}
		}
		std::cout << "#" << i << ": " << collisionPoint.x << ", " << collisionPoint.y << std::endl <<
		"LineHeight: " << p->faces.at(i).b->y << ", " << p->faces.at(i).a->y << std::endl;
	}
	std::cout << "COLLISIONS: " << colliderCount << std::endl;
	return !(colliderCount % 2 == 0);
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

cVertex cSegment::GetIntersection(cSegment *s) {
	cMiscMath m;
	cVertex t;
	double x1 = this->a->x, y1 = this->a->y;
	double x2 = this->b->x, y2 = this->b->y;
	double x3 = s->a->x, y3 = s->a->y;
	double x4 = s->b->x, y4 = s->b->y;
	t.x = m.Determination(m.Determination(x1, y1, x2, y2), m.Determination(x1, 1, x2, 1), 
	                      m.Determination(x3, y3, x4, y4), m.Determination(x3, 1, x4, 1)) / 
	      m.Determination(m.Determination(x1, 1, x2, 1), m.Determination(y1, 1, y2, 1),
	                      m.Determination(x3, 1, x4, 1), m.Determination(y3, 1, y4, 1));
	t.y = m.Determination(m.Determination(x1, y1, x2, y2), m.Determination(y1, 1, y2, 1),
	                      m.Determination(x3, y3, x4, y4), m.Determination(y3, 1, y4, 1)) /
	      m.Determination(m.Determination(x1, 1, x2, 1), m.Determination(y1, 1, y2, 1),
	                      m.Determination(x3, 1, x4, 1), m.Determination(y3, 1, y4, 1));
	return t;
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
