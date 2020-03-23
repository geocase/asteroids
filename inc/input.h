#ifndef INPUT_H
#define INPUT_H

class cInput;

#include "game.h"

class cInput {
public:
	int32_t mouseX, mouseY;
	bool windowExit = false;

	enum eInputType_t currentInput = NONE;

	void Update();
	void UpdateKeyboard();
	void UpdateMouse();
	void WindowEvents();
};

#endif
