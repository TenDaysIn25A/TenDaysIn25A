#pragma once
#include "Dlib.h"

class EnemyHpGauge{
public:
	// ----------------------------------------------
	// メンバ関数
	// ----------------------------------------------

	EnemyHpGauge();

	// 根幹
	// ----------------------------------------------


	/// <summary>
	/// 初期化をここに
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理をここに
	/// </summary>
	void Update();
	
	/// <summary>
	/// 描画処理をここに　※constによってこの中での値の変更は禁止されている。
	/// </summary>
	void Draw() const;

	/// <summary>
	/// mainやGameSceneからカメラを取得してください。
	/// </summary>
	/// <param name="camera"></param>
	void SetCamera(const Transform2D& camera);

	/// <summary>
	/// 敵にダメージを与える
	/// </summary>
	void ReferenceHp(int setHp,int setMaxHp);

	/// <summary>
	/// HPゲージを作成する
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="startHp">初期体力</param>
	/// <param name="setMaxHp">最大体力</param>
	/// <param name="setWidth">横幅</param>
	/// <param name="setHeight">縦幅</param>
	void CreateHpGauge(const Vector2& position, int startHp, int setMaxHp, float setWidth, float setHeight, unsigned int setColor, bool setBackGroundVisible);

	/// <summary>
	/// 敵を倒す
	/// </summary>
	void Destory();

	// システム
	// ----------------------------------------------
	Renderer renderer;  // 描画ライブラリをこれで使えるようにしてください。

	// エネミープロパティ
	// ----------------------------------------------

	Transform2D transform; // positionとか宣言しなくてええんやで

	int hp;
	int maxHp;
	float width;
	float height;

	float gaugeFramePixel;

	float positionXMisalignment;

	const unsigned int kBackGrroundColor = 0x333333FF;
	const unsigned int kColor = 0xFFFFFFFF;

	unsigned int color;
	bool isVisible;
	bool isBackGroundVisible;
};