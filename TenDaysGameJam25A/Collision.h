#pragma once
#include "Vector2.h"

class Collision {
public:
	static int CircleToCircle(const Vector2& posA, const float& radiusA, const Vector2& posB, const float& radiusB);
};
