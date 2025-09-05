#pragma once
#include "SampleSceneDaichi.h"
#include "SampleSceneMidzuki.h"
#include "SampleSceneYuto.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "CreditScene.h"
#include "ConfigScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "BackGround.h"

enum class Scene { TITLE, STAGE_SELECT, CONFIG, CREDIT, INGAME, GAMECLEAR, GAMEOVER,END, COUNT };

class SceneManager {

public:

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
	Input input;

	bool isPause;
	Button buttonToTitleFromPause;
	Button buttonToSelectFromPause;
	Button buttonToContinueFromPause;

};
