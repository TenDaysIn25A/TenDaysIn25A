#pragma once
#include "Dlib.h"

enum class BulletType{
	SHOT,RETURNFISH,SQUID,WAVE,TURN,HERMITCLAB,
};

class Bullet {
public:
	Bullet();
	
	void Initialize();
	
	void Update();
	
	void Draw() const;

	void ShotPos(const Vector2& startPos, const Vector2& endPos, float spreadRotationDegree);
	void WaveDir(const Vector2& startPos, const Vector2& dir, float theta, float amplitude, float waveOffset);
	void TurnDir(const Vector2& startPos, const Vector2& dir, float amplitude);
	void ShotDir(const Vector2& startPos, const Vector2& dir, float spreadRotationDegree);
	void Deactive();

	void SetCamera(const Transform2D& camera);

	void DeactiveOutOfWindow();

	void FishLightShine(const Vector2& lightPos);

	void PlayerBulletHit();

private:
	void Move();
	void FishMove();
	void squidMove();
	void WaveMove();
	void TurnMove();
	void ClabMove();
public:
	// ステータス
	int damage;
	int isActive;
	BulletType type;

	int timer;
	int isLightShines;

	int isTurn;

	float theta;
	float waveAmplitudeY;
	float waveOffsetX;
	float waveOffsetY;
	
	int isHermitClabStop;

	// 物理プロパティ
	float speed;
	Transform2D transform;
	Vector2 direction;
	Vector2 velocity;
	float width;
	float height;

	Transform2D oneDimTransform;

	// 描画プロパティ
	Renderer renderer;
	DrawEffects effect;
	unsigned int color;
	int grHandle;
	int grHandleBox;

	// 音楽
	int auHandleShot;
};
