#include <iostream>

#include "fps.h"
#include "game.h"
#include "sector.h"
#include "window.h"
#include "input.h"

#define NODES 6

int main() {
	srand(time(NULL));
	cWindow primWin;
	cInput primIn;
	cGame primGame;

	cVertex *points = new cVertex[NODES];
	points[0].PlaceAt(primWin.winx / 2, primWin.winy / 2 - 300);
	points[1].PlaceAt(primWin.winx / 2 + 300, primWin.winy / 2 - 300);
	points[2].PlaceAt(primWin.winx / 2 + 300, primWin.winy / 2);
	points[3].PlaceAt(primWin.winx / 2, primWin.winy / 2);
	points[4].PlaceAt(primWin.winx / 2 + 150, primWin.winy / 2 - 20);
	points[5].PlaceAt(primWin.winx / 2, primWin.winy / 2 - 300);

	cVertex *mouse = new cVertex[2];
	mouse[0].PlaceAt(primWin.winx / 2 + 300, primWin.winy / 2 - 300);
	mouse[1].PlaceAt(primWin.winx / 2 + 200, primWin.winy / 2);

	//cPolygon *test = new cPolygon;
	//test->BuildFromVertexArray(points, 5);

	cSegment *mouseLine = new cSegment(&mouse[0], &mouse[1]);
	cSegment *testLine = new cSegment(&points[1], &points[2]);
	sColor_t col;
	col.r = 255;
	col.g = 255;
	col.b = 255;
	col.a = 255;

	cFPS primFPS;
	primFPS.StartFPSCounter();

	primGame.player.PlaceAt(200, 200);
	while(primGame.running) {
		primFPS.StartFrame();
	//	primWin.DrawPolygon(test, col);
		primWin.DrawLine(mouse[0].x, mouse[0].y, mouse[1].x, mouse[1].y, col);
		primWin.DrawLine(points[1].x, points[1].y, points[2].x, points[2].y, col);
		primWin.Update();
		primFPS.EndFrame();


		primIn.Update();
		primGame.Update(&primIn);
//		mouse[0].x = primIn.mouseX;
//		mouse[0].y = primIn.mouseY;
		std::cout << "INTERSECT: " << mouseLine->GetIntersection(testLine).x <<", " 
		<< mouseLine->GetIntersection(testLine).y << std::endl;
	}

	return 0;
}
