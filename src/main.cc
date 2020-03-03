#include <iostream>

#include "sector.h"
#include "window.h"
#include "input.h"

#define NODES 6

int main() {
	srand(time(NULL));
	cWindow primWin;
	cInput primIn;
	cVertex *points = new cVertex[NODES];
	points[0].PlaceAt(primWin.winx / 2, primWin.winy / 2);
	points[1].PlaceAt(primWin.winx / 2 + 100, primWin.winy / 2);
	points[2].PlaceAt(primWin.winx / 2, primWin.winy / 2 - 50);
	points[3].PlaceAt(0, 0);
	points[4].PlaceAt(primWin.winx / 2 + 100, primWin.winy / 2 - 5);
	points[5].PlaceAt(0, 0);

	/*
	for(int l = 0; l < NODES; l++) {
		points[l].PlaceAt(rand() % primWin.winx, rand() % primWin.winy);
	}
	*/
	cPolygon quad;
//	quad.BuildFromVertexArray(points, NODES);	

	cPath p;
	p.BuildFromVertexArray(points, NODES);	

	cSegment *segA = new cSegment(&points[0], &points[1]);
	cSegment *segB = new cSegment(&points[2], &points[3]);
	cSegment *segC = new cSegment(&points[4], &points[5]);

	cVertex tempA;
	cVertex tempB;

	sColor_t col;
	col.r = 255;
	col.g = 255;
	col.b = 255;
	col.a = 255;

	for(int k = 0; k < 15000; k++) {
		
		primWin.DrawLine(segA->a->x, segA->a->y, segA->b->x, segA->b->y, col);
		primWin.DrawLine(segB->a->x, segB->a->y, segB->b->x, segB->b->y, col);
		primWin.DrawLine(segC->a->x, segC->a->y, segC->b->x, segC->b->y, col);

		points[3] = segA->GetPointAt(.1);

		points[5] = segB->GetPointAt(.25);

		points[1].Rotate(points[0].x, points[0].y, .001);
		/*
		for(int i = 0; i < p.lineDefCount; i++) {
			tempA = *(p.lineDefs.at(i).a);
			tempB = *(p.lineDefs.at(i).b);
			primWin.DrawLine(tempA.x, tempA.y, tempB.x, tempB.y, col);
		}
		*/
		primWin.Update();
		primIn.Update();
	}
	std::cout << "linedefs: " << p.lineDefCount << std::endl;

	return 0;
}
