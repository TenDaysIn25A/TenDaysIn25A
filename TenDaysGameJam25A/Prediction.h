#pragma once
#include "Dlib.h"

enum class PredictionType {
	Charge, Diffusion,
};

class Prediction{
public:

	Prediction();

	void Initialize();
	void UpDate();
	void Draw()const;


	/// <summary>
	/// mainやGameSceneからカメラを取得してください。
	/// </summary>
	/// <param name="camera"></param>
	void SetCamera(const Transform2D& camera);


	void LineCharge(const Vector2& position, float setWidth, float setHeight, int setTimerMax);
	void LineChargeScreen(const Vector2& startPos, float width, float hegiht, int timer);

	// ----------------------------------------------
	// メンバ変数
	// ----------------------------------------------

	// システム
	// ----------------------------------------------
	Renderer renderer;  // 描画ライブラリをこれで使えるようにしてください。
	Input input;        // 入力ライブラリをこれで使えるようにしてください。
	DrawEffects effect; // エフェクト描画ライブラリをこれで使えるようにしてください。

	// エネミープロパティ
	// ----------------------------------------------

	Transform2D transform; // positionとか宣言しなくてええんやで

	float speed;
	Vector2 direction;
	Vector2 velocity;

	//エネミーの通常機能
	float width;
	float height;
	float beforeHeight;
	bool isVisible;
	int timer;
	int timerMax;
	PredictionType type;
	Tweening easing;
	Color colorMath;

	const unsigned int kDamageColor = 0xAA5555FF;
	const unsigned int kColor = 0xFFFFFFFF;
	int color;

	// 描画
	// 
	int grHandleBox;
};
