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

	cVertex *mouse = new cVertex;

	cPolygon *test = new cPolygon;
	test->BuildFromVertexArray(points, 5);


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
		primWin.DrawPolygon(test, col);
		primWin.Update();
		primFPS.EndFrame();


		primIn.Update();
		primGame.Update(&primIn);
		mouse->x = primIn.mouseX;
		mouse->y = primIn.mouseY;
		std::cout << mouse->InPolygon(test) << std::endl;
	}

	return 0;
}
