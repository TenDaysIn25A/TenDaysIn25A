#pragma once
#include "Input.h"
#include "Click.h"
#include <Novice.h>
#include "Vector2.h"

class ControlSystem {
public:
	ControlSystem() = default;

	void Update();

	/// <summary>
	/// 上移動キー取得
	/// </summary>
	/// <returns></returns>
	int IsMoveUp();

	/// <summary>
	/// 下移動キー取得
	/// </summary>
	/// <returns></returns>
	int IsMoveDown();

	/// <summary>
	/// 左移動キー取得
	/// </summary>
	/// <returns></returns>
	int IsMoveLeft();

	/// <summary>
	/// 右移動キー取得
	/// </summary>
	/// <returns></returns>
	int IsMoveRight();

	/// <summary>
	/// スティックの方向（ベクトル）
	/// </summary>
	/// <returns></returns>
	Vector2 GetStickDirection();

	/// <summary>
	/// ショットアクションキー取得
	/// </summary>
	/// <returns></returns>
	int IsShot();
	
	/// <summary>
	/// パリィアクションキー取得
	/// </summary>
	/// <returns></returns>
	int IsPary();

	/// <summary>
	/// パリッチアクションキー取得
	/// </summary>
	/// <returns></returns>
	int IsDimensionChange();

	/// <summary>
	/// ポーズ画面に切り替えるキーの取得
	/// </summary>
	/// <returns></returns>
	int IsInPause();

	/// <summary>
	/// 決定キー取得
	/// </summary>
	/// <returns></returns>
	int IsAccept();

	/// <summary>
	/// 戻るキー取得　
	/// </summary>
	/// <returns></returns>
	int IsBack();

private:
	Input input;
	Click click;

	int stickLeftX;
	int stickLeftY;
	//int stickRightX;
	//int stickRightY;

	int checkR2;
	int prevR2;
	int checkL2;
	int prevL2;
};
