#include "Collision.h"

int Collision::CircleToCircle(const Vector2& posA, const float& radiusA, const Vector2& posB, const float& radiusB) { 
	Vector2 ab = posA - posB;

	// 距離を求める
	float distance = sqrtf(powf(ab.x, 2) + powf(ab.y, 2));

	// 距離より二つの図形の半径が長かったら
	return distance <= radiusA + radiusB;

}
