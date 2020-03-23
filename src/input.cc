#include <iostream>
#include <SDL2/SDL.h>

#include "game.h"
#include "input.h"

void cInput::Update() {
	this->UpdateKeyboard();
	this->UpdateMouse();
	this->WindowEvents();
}

void cInput::UpdateKeyboard() {
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if(state[SDL_SCANCODE_W]) {
		this->currentInput = FORWARD;
		return;
	}

	this->currentInput = NONE;
	return;
}

void cInput::UpdateMouse() {
	SDL_PumpEvents();
	SDL_GetMouseState(&this->mouseX, &this->mouseY);
}

void cInput::WindowEvents() {
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0) {
		if(e.type == SDL_QUIT) {
			this->windowExit = true;	
		}
	}
}
