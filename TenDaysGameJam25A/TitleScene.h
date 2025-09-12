#pragma once
#include"Dlib.h"
#include"BackGround.h"
#include"Player.h"


class TitleScene{

public:
	enum ControlerSelectButton {
		NONE,
		TO_STAGE_SELECT,
		TO_END
	};


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
	ControlSystem controler;
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
	const Vector2 kScoreDefaultPos = { -600.0f, 280.0f,};
	const Vector2 kHighScoreDefaultPos = { -600.0f ,180.0f};
	int scoreHeight;
	int highScoreHeight;
	int currentCombo;
	int comboBonus;
	int memMaxCombo;
	Vector2 maxComboPos;
	int maxComboHeight;
	int comboHeight;
	Vector2 comboPos;
	

	//ミニゲーム用の弾
	Bullet bullets[kBulletMax];
	int shotCoolTime;

	// ボタン
	Button buttonToStageSelect;
	//Button buttonToConfig;
	//Button buttonToCredit;
	Button buttonToEnd;
	ControlerSelectButton currentSelectButton;

	//操作両対応告げる
	int grHandleIFirstScreen;
	int firstScreenTimer;
	const int kFirstScreenMaxTimer = 120;
	Transform2D firstScreen;
	float firstScreenWidth;
	float firstScreenHeight;
	unsigned int firstScreenColor;
};

