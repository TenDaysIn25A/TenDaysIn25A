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
	void Draw() const;
	void Activate();

	//=================================
	// メンバ変数
	//=================================

	//システム
	//----------------------------------

	DimensionState dimansionState;
	Input input;
	Click click;

	//プロパティ
	//---------------------------------

	const Vector2 oneDimBGPosTop = { 1280.0f,320.0f };
	const Vector2 midDimBGPosTop = { 1280.0f,360.0f };
	const Vector2 twoDimBGPosTop = { 1280.0f,120.0f };

	const Vector2 oneDimBGPosBottom = { 0.0f,400.0f };
	const Vector2 midDimBGPosBottom = { 0.0f,360.0f };
	const Vector2 twoDimBGPosBottom = { 0.0f,600.0f };

	Vector2 underBGPos;
	Vector2 topBGPos;

	Ease ease = EASE_OUT_QUAD;

	int grHandleHalfBg; 
	bool isChanging;
	float speed;

	int tweenStep;  
	float t;        
	float duration; 

	unsigned int color;

	Vector2 startUnder;
	Vector2 startTop;
	Vector2 midUnder;
	Vector2 midTop;
	Vector2 endUnder;
	Vector2 endTop;
};

