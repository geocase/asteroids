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
	points[0].PlaceAt(primWin.winx / 2, primWin.winy / 2);
	points[1].PlaceAt(primWin.winx / 2 + 100, primWin.winy / 2);
	points[2].PlaceAt(primWin.winx / 2, primWin.winy / 2 - 50);
	points[3].PlaceAt(0, 0);
	points[4].PlaceAt(primWin.winx / 2 + 100, primWin.winy / 2 - 5);
	points[5].PlaceAt(0, 0);

	cPath p;

	cVertex tempA;
	cVertex tempB;

	sColor_t col;
	col.r = 255;
	col.g = 255;
	col.b = 255;
	col.a = 255;

	cFPS primFPS;
	primFPS.StartFPSCounter();

	while(primGame.running) {
		primFPS.StartFrame();
		primWin.DrawPolygon(&(primGame.player.shape), col);

		primIn.Update();
		primGame.Update(&primIn);
		primWin.Update();
		primFPS.EndFrame();
	}

	return 0;
}
