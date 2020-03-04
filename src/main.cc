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

	cEntityAsteroid *aster = new cEntityAsteroid[10];
	
	for(int i = 0; i < 10; i++) {
		aster[i].Translate((rand() % primWin.winx) - 100, (rand() % primWin.winy) - 100);
	}


	while(primGame.running) {
		primFPS.StartFrame();
		primWin.DrawPolygon(&(primGame.player.shape), col);
		for(int i = 0; i < 10; i++) {
			primWin.DrawPolygon(&(aster[i].shape), col);
		}
		primWin.Update();
		primFPS.EndFrame();

		primGame.player.Rotate(1 * primFPS.GetFrameTime());

		for(int i = 0; i < 10; i++) {
			aster[i].Rotate(3 * primFPS.GetFrameTime());
		}

		std::cout << primGame.player.xPos << ", " << primGame.player.yPos << std::endl;
		std::cout << primGame.player.angle << std::endl;
		primIn.Update();
		primGame.Update(&primIn);

		std::cout << primFPS.GetFrameTime() << std::endl;
	}

	return 0;
}
