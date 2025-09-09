#pragma once
#include "Input.h"
#include "Click.h"
#include <Novice.h>

class ControlSystem {
public:
	ControlSystem() = default;

	void Update();

	int IsMoveUp();
	int IsMoveDown();
	int IsMoveLeft();
	int IsMoveRight();
	int IsShot();
	int IsPary();
	int IsDimensionChange();

private:
	Input input;
	Click click;

	int stickLeftX;
	int stickLeftY;
	//int stickRightX;
	//int stickRightY;
};
