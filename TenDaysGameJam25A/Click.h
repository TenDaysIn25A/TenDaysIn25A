#pragma once
#include <Novice.h>

class Click {
public:
	Click() = default;
	~Click() = default;

	// 入力を取得
	void Update();

	/// <summary>
	/// 押している間
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	int GetClick(unsigned char clickCode) { return static_cast<unsigned char>(clicks_[clickCode]); }

	int GetPreClick(unsigned char clickCode) { return static_cast<unsigned char>(preClicks_[clickCode]); }

	/// <summary>
	/// 離したとき
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	int GetClickRelease(unsigned char clickCode) { return !static_cast<unsigned char>(clicks_[clickCode]) && static_cast<unsigned char>(preClicks_[clickCode]); }

	/// <summary>
	/// 押したとき
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	int GetClickTrigger(unsigned char clickCode) { return static_cast<unsigned char>(clicks_[clickCode]) && !static_cast<unsigned char>(preClicks_[clickCode]); }

	/// <summary>
	/// 何も押されていない
	/// </summary>
	/// <param name="keyCode"></param>
	/// <returns></returns>
	int GetClickNotAnswer(unsigned char clickCode) { return !static_cast<unsigned char>(clicks_[clickCode]) && !static_cast<unsigned char>(preClicks_[clickCode]); }

private:
	// staticな変数は値が共有される。
	int clicks_[8] = { 0 };
	int preClicks_[8] = { 0 };
};

