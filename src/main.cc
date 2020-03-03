#include <iostream>

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

	while(primGame.running) {
		for(int i = 0; i < primGame.player.shape.faceCount; i++) {
			tempA = *(primGame.player.shape.faces.at(i).a);
			tempB = *(primGame.player.shape.faces.at(i).b);
			primWin.DrawLine(tempA.x, tempA.y, tempB.x, tempB.y, col);
		}		
		std::cout << primGame.player.shape.faceCount << std::endl;	

		primIn.Update();
		primGame.Update(&primIn);
		primWin.Update();
	}

	return 0;
}
