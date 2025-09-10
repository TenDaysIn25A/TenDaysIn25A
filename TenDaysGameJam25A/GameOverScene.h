#pragma once
#include"Dlib.h"
class GameOverScene{

public:

	enum ControlerSelectButton{
		NONE,
		TO_RETRY,
		TO_STAGESELECT
	};

	//==============================
	// メンバ関数
	//==============================
	GameOverScene();

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
	Button buttonToRetry;
	Button buttonToStageSelect;
	ControlSystem controler;
	ControlerSelectButton currentSelectButton;

	//プロパティ
	//------------------------------
	float width;
	float height;

	int grHandle;
};

