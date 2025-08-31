#pragma once
#include "Vector2.h"

class Collision {
public:
	static int CircleToCircle(const Vector2& posA, const float& radiusA, const Vector2& posB, const float& radiusB);
	int BoxToPoint(const Vector2& pointPos, const Vector2& boxCenter, const float& width, const float& height);
};
