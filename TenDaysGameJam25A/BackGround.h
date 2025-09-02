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

	const Vector2 underTwoDirBGPos = { 0.0f,600.0f };
	const Vector2 topTwoDirBGPos = { 1280.0f,120.0f };

	const Vector2 underOneDirBGPos = { 0.0f,400.0f };
	const Vector2 topOneDirBGPos = { 1280.0f,320.0f };

	Vector2 underBGPos;
	Vector2 topBGPos;

	int grHandleHalfBg; 
	bool isChanging;
	float speed;



};

