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
	void MiniGameInitialize();
	void MiniGame();
	void MiniGameCheckHitAll();

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
	BitMapFont font;



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
	int memHighScore;
	int grHandleChiriri;

	Vector2 scorePos;
	Vector2 highScorePos;
	const Vector2 kScoreDefaultPos = { -600.0f, 180.0f,};
	const Vector2 kHighScoreDefaultPos = { -600.0f ,280};
	int scoreHeight;
	int highScoreHeight;
	int currentCombo;
	int comboBonus;
	int memHighCombo;
	int comboHeight;
	Vector2 comboPos;
	

	//ミニゲーム用の弾
	Bullet bullets[kBulletMax];
	int shotCoolTime;



	// ボタン
	Button buttonToStageSelect;
	Button buttonToConfig;
	Button buttonToCredit;
	Button buttonToEnd;

};

