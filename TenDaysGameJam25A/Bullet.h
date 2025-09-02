#pragma once
#include "Dlib.h"
class Bullet {
public:
	Bullet();
	
	void Initialize();
	
	void Update();
	
	void Draw() const;

	void ShotPos(const Vector2& startPos, const Vector2& endPos, float spreadRotationDegree);
	void ShotDir(const Vector2& startPos, const Vector2& dir, float spreadRotationDegree);
	void Deactive();

	void SetCamera(const Transform2D& camera);

private:
	void Move();

public:
	// ステータス
	int damage;
	int isActive;
	
	// 物理プロパティ
	float speed;
	Transform2D transform;
	Vector2 direction;
	Vector2 velocity;
	float width;
	float height;

	// 描画プロパティ
	Renderer renderer;
	DrawEffects effect;
	unsigned int color;
	int grHandle;
};
