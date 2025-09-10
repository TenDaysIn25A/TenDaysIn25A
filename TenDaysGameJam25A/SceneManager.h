#pragma once
#include "BackGround.h"
#include "ConfigScene.h"
#include "CreditScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "SampleSceneDaichi.h"
#include "SampleSceneMidzuki.h"
#include "SampleSceneYuto.h"
#include "StageSelectScene.h"
#include "TitleScene.h"

enum class Scene { TITLE, STAGE_SELECT, CONFIG, CREDIT, INGAME, GAMECLEAR, GAMEOVER, END, COUNT };

class SceneManager {

public:
	enum ControlerSelectButton { NONE, TO_TITLE, TO_SELECT, TO_CONTINUE };

	//============================
	// メンバ関数
	//============================

	SceneManager();

	void Initialize();
	void Update();
	void ExchangeScene(Scene changeScene);

	//==============================
	// メンバ変数
	//==============================

	Scene currentScene;
	TitleScene titleScene;
	StageSelectScene stageSelectScene;
	ConfigScene configScene;
	CreditScene creditScene;
	GameScene gameScene;
	GameClearScene gameClearScene;
	GameOverScene gameOverScene;
	// Input input;

	bool isPause;
	Button buttonToTitle;
	Button buttonToSelect;
	Button buttonToContinue;

	ControlSystem controler;
	ControlerSelectButton currentSelectButton;

	float currentBgmVolume;
	const float kBgmVolume = 0.1f;
	int bgmPlayHandle;
	int auHandleTitle;
	int auHandleStageTutorial;
	int auHandleStage1;
	int auHandleResult;

};
