#include "Collision.h"

int Collision::CircleToCircle(const Vector2& posA, const float& radiusA, const Vector2& posB, const float& radiusB) { 
	Vector2 ab = posA - posB;

	// 距離を求める
	float distance = sqrtf(powf(ab.x, 2) + powf(ab.y, 2));

	// 距離より二つの図形の半径が長かったら
	return distance <= radiusA + radiusB;

}

int Collision::BoxToPoint(const Vector2& pointPos, const Vector2& boxCenter, const float& width, const float& height) {

	float boxLeft = boxCenter.x - width / 2.0f;
	float boxRight = boxCenter.x + width / 2.0f;
	float boxTop = boxCenter.y + height / 2.0f;
	float boxBottom = boxCenter.y - height / 2.0f;

	bool resultX = pointPos.x >= boxLeft && pointPos.x <= boxRight;
	bool resultY = pointPos.y <= boxTop && pointPos.y >= boxBottom;

	return (resultX && resultY);
}
