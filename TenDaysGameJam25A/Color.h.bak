#pragma once
#include <Math.h>

enum Pallet { CHOCO_MINT, YELLOW, COUNT };

namespace ColorPallet {
inline Pallet pallet;

constexpr unsigned int BACK_GROUND[Pallet::COUNT] = {0x7A5F58FF, 0xDDDD00FF};
constexpr unsigned int ENEMY[Pallet::COUNT] = {0xFA3F18FF, 0xDDDD00FF};
constexpr unsigned int PLAYER[Pallet::COUNT] = {0xFFFFFFFF, 0xFFFFFFFF};
constexpr unsigned int PLAYER_ATTACK[Pallet::COUNT] = {0x37FABAFF, 0x00FFFFFF};
constexpr unsigned int PLAYER_DEFENCE[Pallet::COUNT] = {0x37FABAFF, 0x00FFFFFF};

} // namespace Color

enum class PickUpColor {
	kPickUpRed,
	kPickUpGreen,
	kPickUpBlue,
	kPickUpAlpha
};

class Color {
public:

	/// <summary>
	/// 赤、緑、青、透明度を入力すると8桁のカラーコードとして返す
	/// </summary>
	/// <param name="red">赤の16進数</param>
	/// <param name="green">緑の16進数</param>
	/// <param name="blue">青の16進数</param>
	/// <param name="alpha">透明度の16進数</param>
	/// <returns></returns>
	static unsigned int RGBCreator(int red, int green, int blue, int alpha);

	/// <summary>
	/// 8桁のカラーコード、取得する要素を入力するすると対応する2桁の16進数を返す
	/// </summary>
	/// <param name="color">8桁のカラーコード</param>
	/// <param name="pickUpColor">取得する要素</param>
	/// <returns></returns>
	static int RGBPickUp(unsigned int color, PickUpColor pickUpColor);
};