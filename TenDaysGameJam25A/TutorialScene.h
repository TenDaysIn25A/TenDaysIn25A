#pragma once
#include"Dlib.h"
#include"BackGround.h"
#include"Zako.h"

class TutorialScene{

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

	int currentTutorialLevel;
	const int tutorialEndLevel = 5;
	int startTimer;
	const int kTutorialInterval = 180;
	int intervalTimer;
};

