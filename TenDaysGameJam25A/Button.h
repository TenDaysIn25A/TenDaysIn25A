#pragma once
#include"Dlib.h"

enum class ButtonState{
	NONE,
	HOVER,
	CLICKED
};

class Button {
public:
	Button();

	// メンバ関数
	// ----------------------------------------

	void Initialize();
	void Initialize(int textureHandle, float w , float h);
	void Update();
	void Draw() const;

	void GetMousePos();
	void CheckHitCursor();

	bool IsNone();
	bool IsHover();
	bool IsClicked();

	// メンバ変数
	// ----------------------------------------

	// プロパティ
	Transform2D transform;
	
	// 描画
	Renderer renderer;
	Transform2D camera;
	
	// イージング
	float duration;
	float t;
	int tweenStepHovered;
	Ease ease;

	// マウス
	Vector2 mousePos;

	// 状態
	ButtonState state;
	
	// 各状態のスケール
	float scaleNone;
	float scaleHover;
	float scaleCliked;

	// グラフハンドル
	int grHandle;
	float width;
	float height;
	unsigned int color;
};
