#pragma once
#include"Dlib.h"
#include"BackGround.h"
#include"Zako.h"

class TutorialScene {

public:

	//================================
	// メンバ関数
	//================================
	TutorialScene();

	void Initialize();
	void Update();
	void Draw()const;

	Zako zako;
	BackGround backGround;
	Renderer renderer;
	Input input;
	Click click;


	int currentTutorialLevel;
	const int tutorialEndLevel = 5;
	int startTimer;
	const int kTutorialInterval = 180;
	int intervalTimer;
	bool isSafe;
	bool isShot;

	//テキスト位置
	Transform2D tutorialFukidashi;
	Transform2D tutorialText;
	float howToMoveWidth;
	float howToMoveHeight;
	float howToShotWidth;
	float howToShotHeight;
	float howToParittiWidth;
	float howToParittiHeight;
	float howToParryWidth;
	float howToParryHeight;
	float fukidashiWidth;
	float fukidashiHeight;

	const float kTextOffsetY = 60.0f;

	//UI位置
	Transform2D info;
	Transform2D infoButton;
	float infoParryHeight;
	float infoParryWidth;
	float infoShotHeight;
	float infoShotWidth;
	float infoButtonWidth;
	float infoButtonHeight;
	const Vector2 kInfoOffset = { 140.0f,-40.0f };

	//グラフハンドル
	int grHandleHowToMove;
	int grHandleHowToShot;
	int grHandleHowToParitti;
	int grHandleHowToParry;

	int grHandleInfoA;
	int grHandleInfoB;
	int grHandleInfoParry;
	int grHandleInfoShot;

	int grHandleFukidashi;

	bool isClear;
};

