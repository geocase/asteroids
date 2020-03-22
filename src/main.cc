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
		ast[i].speed = rand() % 100;
	}
	
	primGame.player.speed = 50;
	while(primGame.running) {
		primFPS.StartFrame();
		for(int i = 0; i < 10; i++) {
			if(!ast[i].dead) {
				if(primGame.player.shape.PartiallyInPolygon(&(ast[i].shape))) {
					primWin.DrawPolygon(&(ast[i].shape), red);
					ast[i].SetSize(ast[i].size - 1);
				} else {
					primWin.DrawPolygon(&(ast[i].shape), col);
				}
			}
		}
		primWin.DrawPolygon(&(primGame.player.shape), col);
		primWin.Update();
		primFPS.EndFrame();

		for(int i = 0; i < 10; i++) {
			if(!ast[i].dead) {
				ast[i].Rotate(.6 * primFPS.GetFrameTime());
				ast[i].Update(primFPS.GetFrameTime());
				ast[i].ThrustForward();
			} else {
				ast[i].dead = false;
				ast[i].SetSize(ast[i].maximumSize);
				ast[i].PlaceAt(rand() % primWin.winx, rand() % primWin.winy);
			}
		}

		primGame.player.Rotate(0.349066 * primFPS.GetFrameTime());
		primGame.player.ThrustForward();
		primGame.player.Update(primFPS.GetFrameTime());
		primIn.Update();
		
		primGame.Update(&primIn);
		std::cout << primGame.player.position.x << ", " << primGame.player.position.y << std::endl;
		std::cout << primGame.player.position.z << std::endl;
		std::cout << "Frametime: " << primFPS.GetFrameTime() << std::endl;
	}

	return 0;
}
