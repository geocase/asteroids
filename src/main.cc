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
	
	while(primGame.running) {
		primFPS.StartFrame();
		for(int i = 0; i < 10; i++) {
			if(primGame.player.shape.PartiallyInPolygon(&(ast[i].shape))) {
				primWin.DrawPolygon(&(ast[i].shape), red);
			} else {
				primWin.DrawPolygon(&(ast[i].shape), col);
			}
		}
		primWin.DrawPolygon(&(primGame.player.shape), col);
		primWin.Update();
		primFPS.EndFrame();

		for(int i = 0; i < 10; i++) {
			ast[i].Rotate(1 * primFPS.GetFrameTime());
		}

		primGame.player.PlaceAt(primIn.mouseX, primIn.mouseY);
		primIn.Update();
		primGame.Update(&primIn);
		std::cout << "Frametime: " << primFPS.GetFrameTime() << std::endl;
	}

	return 0;
}
