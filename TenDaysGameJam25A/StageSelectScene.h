#pragma once
#include"Dlib.h"

class StageSelectScene {
public:

	enum ControlerSelectButton { TO_NONE, TO_RIGHTSIDE, TO_LEFTSIDE, TO_STAGE, TO_TITLE };

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
	Stage memCurrentStage;
	ControlSystem controler;

	// ボタン
	//----------------------------------
	Button buttonToRightSide;
	Button buttonToLeftSide;
	Button buttonToStage;
	Button buttonToTitle;
	ControlerSelectButton currentSelectButton;

	// バックグラウンド
	Transform2D backGround;

	//プロパティ
	//------------------------------
	float width;
	float height;

	int grHandle;

	Vector2 tutorialDefault;

	Vector2 chochinStageDefault;
	float animationFirtSpeed;
	float kAnimationAcceleration  = 8.0f;


	Transform2D chochinLight;
	float chochinLightWidth;
	float chochinLightHeight;
	int grHandleStageSelectChochinLight0;
	int grHandleStageSelectChochinLight1;
	int grHandleStageSelectChochinLight2;
	int grHandleStageSelectChochinLight3;
	float chochinLightTheta;
	const float kChochinLightOffsetX = 0.0f;
	const float kChochinLightOffsetY =360.0f;
	int chochinAnimationCount;

	Transform2D chochinStageColorText;
	int grHandleChochinStageColorText;
	const float chochinStageColorTextOffsetX = -284.0f;
	float chochinStageColorTextWidth;
	float chochinStageColorTextHeight;
	unsigned int chochinStageColorTextColor;
	int chochinStageTextColorChongeTimer;

	Transform2D chochinStageWhiteText;
	int grHandleChochinStageWhiteText;
	float chochinStageWhiteTextWidth;
	float chochinStageWhiteTextHeight;
	const Vector2 kChochinStageWhiteTextOffset = { 60.0f,0.0f };

	Transform2D tutorialFishBone;
	float tutorialFishBoneWidth;
	float tutorialFishBoneHeight;
	int grHandleTutorialFishBone;

	Transform2D tutorialStageText;
	int grhandleTutorialStageText;
	float tutorialStageTextWidth;
	float tutorialStageTextHeight;
	const Vector2 kTutorialStageTextOffset = { 0.0f,110.0f };

	float textAmplitudeY;
	float textWavingThetaY;

	bool isAnimationLeftMove;
	bool isAnimationRightMove;
	bool isTutorialCleared;
};

