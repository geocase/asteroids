#include <iostream>
#include <SDL2/SDL.h>

#include "input.h"

void cInput::Update() {
	SDL_PumpEvents();
	SDL_GetMouseState(&this->mouseX, &this->mouseY);
}
