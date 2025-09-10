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

	/// <summary>
	/// 予告線を作成する
	/// </summary>
	/// <param name="position">予告線の位置</param>
	/// <param name="setWidth">予告線の横幅</param>
	/// <param name="setHeight">予告線の縦幅</param>
	/// <param name="setTimerMax">予告線を表示するフレームの長さ</param>
	void LineCharge(const Vector2& position, float setWidth, float setHeight, int setTimerMax);

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
	bool isActive;
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
