#ifndef SECTOR_H
#define SECTOR_H

#include <vector>

class cVertex;
class cSegment;
class cPolygon;

class cPath;

class cVertex {
public:
	double x = 0, y = 0;
	
	void Rotate(const double ax, const double ay, const double r);
	void PlaceAt(const double nx, const double ny);
};

class cSegment {
public:
	cVertex *a, *b;

	cSegment(double ax, double ay, double bx, double by);
	cSegment(cVertex *na, cVertex *nb);

	cVertex GetPointAt(double ratio);
};

class cPolygon  {
public:
	std::vector<cSegment> faces;
	uint32_t faceCount = 0;

	void AddFace(const cSegment *l);
	void BuildFromVertexArray(cVertex *p, uint32_t nc);
};

class cPath {
public:
	std::vector<cSegment> lineDefs;
	uint32_t lineDefCount = 0;
	void AddSegment( const cSegment *l);
	void BuildFromVertexArray(cVertex *p, uint32_t nc);
};
#endif
