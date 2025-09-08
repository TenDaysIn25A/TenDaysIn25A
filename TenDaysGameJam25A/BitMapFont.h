#pragma once
#include <vector> 
#include <math.h>
#include <Novice.h>
#include "Renderer.h"

class BitMapFont {
public:
	BitMapFont();
	~BitMapFont() = default;

	/// <summary>
	/// 数字を描画する。
	/// </summary>
	/// <param name="position">中心座標（ワールド）</param>
	/// <param name="num">描画したい数字</param>
	/// <param name="fonsSize">height基準</param>
	/// <param name="letterSpacing">間隔のこと 0が基準</param>
	/// <param name="color">色</param>
	void DrawNumber(const Vector2& position, int num, int fontSize, float letterSpacing, unsigned int color) const;

private:
	Renderer renderer_;
	Transform2D transform_;
	const float kFontWidth_ = 256.0f;
	const float kFontHeight_ = 256.0f;
	int grHandleFonts_[10];
};
