#include "BitMapFont.h"

BitMapFont::BitMapFont() {
	grHandleFonts_[0] = Novice::LoadTexture("./Resources/images/f0.png");
	grHandleFonts_[1] = Novice::LoadTexture("./Resources/images/f1.png");
	grHandleFonts_[2] = Novice::LoadTexture("./Resources/images/f2.png");
	grHandleFonts_[3] = Novice::LoadTexture("./Resources/images/f3.png");
	grHandleFonts_[4] = Novice::LoadTexture("./Resources/images/f4.png");
	grHandleFonts_[5] = Novice::LoadTexture("./Resources/images/f5.png");
	grHandleFonts_[6] = Novice::LoadTexture("./Resources/images/f6.png");
	grHandleFonts_[7] = Novice::LoadTexture("./Resources/images/f7.png");
	grHandleFonts_[8] = Novice::LoadTexture("./Resources/images/f8.png");
	grHandleFonts_[9] = Novice::LoadTexture("./Resources/images/f9.png");
}

void BitMapFont::DrawNumber(const Vector2& position, int num, int fontSize, float letterSpacing, unsigned int color) const {
	//フォントのスケール
	float fontScale = static_cast<float>(fontSize) / kFontWidth_;
	
	//フォントの間隔
	float fontLetterSpacing = fontSize / 2.0f + letterSpacing;

	// 桁数を自動で求める（もし0のときは1桁）
	// log10(数値)+1の結果を小数点以下切り捨て(intにcast)すると、その数値の桁数がわかる
	int numDigits = 0;
	if (num == 0) {
		numDigits = 1;
	} else {
		numDigits = static_cast<int>(log10(num)) + 1;
	}

	// 一番上の桁から順番に数字を算出してリストに要素を追加（上の桁からなのでカウントダウン）
	int targetNumber = num;      
	std::vector<int> targetList; 
	for (int i = numDigits; i > 0; i--) {
		// 現在の桁の重み
		int divisor = static_cast<int>(pow(10, i - 1));

		// 現在の桁の数字
		int digit = targetNumber / divisor;

		// 現在の桁の数字をリストに代入
		targetList.push_back(digit);

		// リストに代入できた桁を除く
		targetNumber %= divisor;
	}

	
	// ターゲットの桁数分繰り返す
	std::vector<Transform2D> fontTransforms;
	for (int i = 0; i < numDigits; i++) {
		// 桁数による位置を決める
		Transform2D t;
		
		t.position = {position.x + (i * fontLetterSpacing), position.y};
		t.scale = {fontScale, fontScale};
		fontTransforms.push_back(t);

		// フォントに対応した数字の描画
		renderer_.DrawSprite(fontTransforms[i], kFontWidth_, kFontHeight_, 0.0f, grHandleFonts_[targetList[i]], color);
	}
}
