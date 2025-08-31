#pragma once
#include <Novice.h>

class Input {
public:
	Input() = default;
	~Input() = default;

	// 入力を取得
	void Update();

	/// <summary>
	/// 押している間
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	int GetKey(unsigned char keyCode) { return static_cast<unsigned char>(keys_[keyCode]); }

	int GetPreKey(unsigned char keyCode) { return static_cast<unsigned char>(preKeys_[keyCode]); }

	/// <summary>
	/// 離したとき
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	int GetKeyRelease(unsigned char keyCode) { return !static_cast<unsigned char>(keys_[keyCode]) && static_cast<unsigned char>(preKeys_[keyCode]); }

	/// <summary>
	/// 押したとき
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	int GetKeyTrigger(unsigned char keyCode) { return static_cast<unsigned char>(keys_[keyCode]) && !static_cast<unsigned char>(preKeys_[keyCode]); }

	/// <summary>
	/// 何も押されていない
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	int GetKeyNotAnswer(unsigned char keyCode) { return !static_cast<unsigned char>(keys_[keyCode]) && !static_cast<unsigned char>(preKeys_[keyCode]); }

private:
	// staticな変数は値が共有される。
	char keys_[256];
	char preKeys_[256];
};
