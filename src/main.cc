#include <iostream>

#include "fps.h"
#include "game.h"
#include "sector.h"
#include "window.h"
#include "input.h"

#define NODES 7

int main() {
	srand(time(NULL));
	cWindow primWin;
	cInput primIn;
	cGame primGame;

	cVertex *points = new cVertex[NODES];
	points[0].PlaceAt(primWin.winx / 2, primWin.winy / 2 - 200);
	points[1].PlaceAt(primWin.winx / 2 - 10, primWin.winy / 2 - 400);
	points[2].PlaceAt(primWin.winx / 2 + 300, primWin.winy / 2 - 300);
	points[3].PlaceAt(primWin.winx / 2 + 300, primWin.winy / 2);
	points[4].PlaceAt(primWin.winx / 2, primWin.winy / 2);
	points[5].PlaceAt(primWin.winx / 2 + 250, primWin.winy / 2 - 20);
	points[6].PlaceAt(primWin.winx / 2, primWin.winy / 2 - 300);

	cVertex *mouse = new cVertex[2];
	mouse[0].PlaceAt(primWin.winx / 2 - 300, primWin.winy / 2);

	cPolygon *test = new cPolygon;
	test->BuildFromVertexArray(points, 7);

	cSegment *mouseLine = new cSegment(&mouse[0], &mouse[1]);
	cSegment *testLine = new cSegment(&points[1], &points[2]);
	sColor_t col;
	col.r = 255;
	col.g = 255;
	col.b = 255;
	col.a = 255;

	sColor_t red;
	red.r = 255;
	red.g = 0;
	red.b = 0;
	red.a = 255;

	cFPS primFPS;
	primFPS.StartFPSCounter();

	cEntityAsteroid *ast = new cEntityAsteroid[10];
	for(int i = 0; i < 10; i++) {
		ast[i].PlaceAt(rand() % primWin.winx, rand() % primWin.winy);
	}
	primGame.player.PlaceAt(200, 200);
	
	while(primGame.running) {
		primFPS.StartFrame();
		for(int i = 0; i < 10; i++) {
			if(mouse[1].InPolygon(&(ast[i].shape))) {
				primWin.DrawPolygon(&(ast[i].shape), red);
			} else {
				primWin.DrawPolygon(&(ast[i].shape), col);
			}
		}
		primWin.DrawLine(mouse[0].x, mouse[0].y, mouse[1].x, mouse[1].y, col);
		primWin.Update();
		primFPS.EndFrame();

		for(int i = 0; i < 10; i++) {
			ast[i].Rotate(1 * primFPS.GetFrameTime());
		}


		primIn.Update();
		primGame.Update(&primIn);
		mouse[1].x = primIn.mouseX;
		mouse[1].y = primIn.mouseY;
		std::cout << mouse[1].x << ", " << mouse[1].y << std::endl;
		std::cout << "Frametime: " << primFPS.GetFrameTime() << std::endl;
	}

	return 0;
}
