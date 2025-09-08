#pragma once
#include "Dlib.h"

class Laser{
public:

	Laser();

	void Initialize();
	void Update();
	void Draw()const;


	/// <summary>
	/// mainやGameSceneからカメラを取得してください。
	/// </summary>
	/// <param name="camera"></param>
	void SetCamera(const Transform2D& camera);

	/// <summary>
	/// レーザーを作成する
	/// </summary>
	/// <param name="position">レーザーの位置</param>
	/// <param name="setWidth">レーザーの横幅</param>
	/// <param name="setHeight">レーザーの縦幅</param>
	/// <param name="setTimerMax">レーザーを表示するフレームの長さ</param>
	void LaserCreate(const Vector2& position, float setWidth, float setHeight, int setTimerMax);

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

	float width;
	float height;
	float beforeHeight;
	bool isActive;
	int timer;
	int timerMax;
	Tweening easing;

	const unsigned int kColor = 0xFFFFFFFF;
	int color;

	// 描画
	// 
	int grHandleBox;
};

