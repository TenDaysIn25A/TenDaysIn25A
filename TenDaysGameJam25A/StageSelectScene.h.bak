#pragma once
#include"Dlib.h"

class StageSelectScene {

public:

	//==============================
	// メンバ関数
	//==============================
	
	StageSelectScene();

	void Initialize();
	void Update();
	void Draw() const;
	void SetCamera();

	//===============================
	// メンバ変数
	//===============================

	//システム
	//----------------------------------
	Input input;
	Renderer renderer;
	DrawEffects drawEffects;
	Transform2D transform;
	Stage currentStage;
	Button buttonToRightSide;
	Button buttonToLeftSide;
	Button buttonToStage;
	Button buttonToTitle;

	//プロパティ
	//------------------------------
	float width;
	float height;

	int grHandle;

};

