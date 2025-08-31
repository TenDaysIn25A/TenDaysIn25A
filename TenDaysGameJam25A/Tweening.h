#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

enum Ease { LINEAR, EASE_IN_QUAD, EASE_OUT_QUAD, EASE_INOUT_QUAD };

class Tweening {
public:
	static float Easing(float t, Ease ease);

private:
};
