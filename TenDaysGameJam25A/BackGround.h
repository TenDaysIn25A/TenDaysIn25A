#pragma once
#include"Dlib.h"

class BackGround{

public:

	//==================================
	// メンバ関数
	//==================================

	BackGround();

	void Initialize();
	void Update();
	void Draw();

	//=================================
	// メンバ変数
	//=================================

	//システム
	//----------------------------------

	DimensionState dimansionState;
	Input input;

	//プロパティ
	//---------------------------------

	const Vector2 twoDimBGPosBottom = { 0.0f,600.0f };
	const Vector2 twoDimBGPosTop = { 1280.0f,120.0f };

	const Vector2 oneDimBGPosBottom = { 0.0f,400.0f };
	const Vector2 oneDimBGPosTop = { 1280.0f,320.0f };

	Vector2 underBGPos;
	Vector2 topBGPos;

	int grHandleHalfBg; 
	bool isChanging;
	float speed;
};

