#pragma once
#include"Dlib.h"

class Light{

public:

	//==============================
	// メンバ関数
	//==============================
	Light();

	void Initialize();
	void Update();
	void Draw()const;

	int isPlayerInTheShadow(Transform2D& enemyBullet,float enemyBulletWidth, float enemyBulletHeight, Vector2& target);

	int isTargetLeftOfLight(Vector2& posA,Vector2& target);

	int isTargetRightOfLight(Vector2& posA, Vector2& target);

	void DrawShadow(Transform2D& enemyBullet, float enemyBulletWidth, float enemyBulletHeight);

	//===============================
	// メンバ変数
	//===============================

	Transform2D transform;
	Input input;
	DimensionState dimensionState;
	Renderer renderer;

	Vector2 radius;
	
	float cross;

	bool isActive;


};

