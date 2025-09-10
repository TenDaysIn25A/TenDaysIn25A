#pragma once
#include"Dlib.h"

class GameClearScene{

public:
	enum ControlerSelectButton { NONE, TO_RETRY, TO_STAGESELECT };


	//==============================
	// メンバ関数
	//==============================
	GameClearScene();

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
	int grHandleGoBackTitle;
	int grHandleRestart;
};

