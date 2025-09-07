#pragma once
#include"Dlib.h"
#include"BackGround.h"
#include"Player.h"

class TitleScene{

public:

	//==============================
	// メンバ関数
	//==============================
	TitleScene();

	void Initialize();
	void Update();
	void Draw() const;
	void SetCamera();
	void MiniGame();
	void MiniGameCheckHitAl();

	//===============================
	// メンバ変数
	//===============================

	//システム
	//----------------------------------
	Input input;
	Click click;
	Renderer renderer;
	DrawEffects drawEffects;
	Transform2D transform;
	BackGround backGround;
	Player player;
	Transform2D Chiriri;

	//プロパティ
	//------------------------------
	static constexpr int kBulletMax = 64;
	float width;
	float height;

	int grHandle;
	int miniGameEndTime;
	bool isEndMinigame;
	bool isStartMinigame;
	int miniGameScore;
	int grHandleChiriri;

	//ミニゲーム用の弾
	Bullet bullets[kBulletMax];
	int shotCoolTime;

	// ボタン
	Button buttonToStageSelect;
	Button buttonToConfig;
	Button buttonToCredit;
	Button buttonToEnd;

};

