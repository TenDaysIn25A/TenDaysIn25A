#pragma once
#include"Dlib.h"

class ConfigScene{

public:

	//==============================
	// メンバ関数
	//==============================
	ConfigScene();

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


	//プロパティ
	//------------------------------
	float width;
	float height;

	int grHandle;

};

