#pragma once
#include "Dlib.h"
#include "Parry.h"
#include"Bullet.h"

class Player {
public:
	// ----------------------------------------------
	// メンバ関数
	// ----------------------------------------------

	Player(); // 宣言時に自動で初期化
	~Player() = default;

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

	// アクセッサ (Set～とか、Get～とか)
	// ----------------------------------------------

	/// <summary>
	/// mainやGameSceneからカメラを取得してください。
	/// </summary>
	/// <param name="camera"></param>
	void SetCamera(const Transform2D& camera);

	// 機能
	// ----------------------------------------------

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 画面内にクランプする。
	/// </summary>
	void ClampInWindow2D();

	/// <summary>
	/// 中央に揃える。
	/// </summary>
	void ClampInWindow1D();

	void Destroy();

	// ----------------------------------------------
	// メンバ変数
	// ----------------------------------------------

	// システム
	// ----------------------------------------------
	Renderer renderer;  // 描画ライブラリをこれで使えるようにしてください。
	Input input;        // 入力ライブラリをこれで使えるようにしてください。
	DrawEffects effect; // エフェクト描画ライブラリをこれで使えるようにしてください。

	// プレイヤープロパティ
	// ----------------------------------------------
	Transform2D transform;

	float speed;
	Vector2 direction;
	Vector2 velocity;

	float width;
	float height;

	static constexpr int kBulletMax = 64;

	int shotTimer;
	int isShot[kBulletMax];
	const int kShotCoolTime = 10;

	const int kUpedDamage = 10;
	const int kDefaultDamage = 2;
	int damageUpTime;

	// ステータス
	// ----------------------------------------------
	int life;
	int invincibleTimer;

	bool isHit;
	bool isAlive;
	bool isUpDamage;

	// 包含オブジェクト
	// ----------------------------------------------
	Parry parry;
	Bullet bullets[kBulletMax];

	// 描画
	// ----------------------------------------------
	int grHandleCaracter;

};
