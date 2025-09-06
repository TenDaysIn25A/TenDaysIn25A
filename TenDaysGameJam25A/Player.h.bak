#pragma once
#include "Dlib.h"
#include "Parry.h"
#include "Bullet.h"
#include "Reaction.h"
#include"backGround.h"

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

	/// <summary>
	/// ダメージを取らせる。
	/// </summary>
	void TakeDamage(int damage);

	void Destroy();

	// ----------------------------------------------
	// メンバ変数
	// ----------------------------------------------

	// システム
	// ----------------------------------------------
	Renderer renderer;  // 描画ライブラリをこれで使えるようにしてください。
	Input input;        // 入力ライブラリをこれで使えるようにしてください。
	DrawEffects effect; // エフェクト描画ライブラリをこれで使えるようにしてください。
	Reaction miss;
	Reaction nice;
	Reaction just;
	BackGround backGround;
	Click click;

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
	int shotCoolTime;
	const int kUpedShotCoolTime = 5;
	const int kDefaultShotCoolTime = 10;

	const int kParryTimer = 2;
	const int kUpedDamage = 4;
	const int kDefaultDamage = 2;
	int damageUpTime;

	Transform2D stamina;
	const float kStaminaHeight = 60.0f;
	int grhandleStamina;

	Transform2D life[3];
	const float lifeWidth = 50.0f;
	const float lifeHeight = 50.0f;
	int grhandleLife;

	// ステータス
	// ----------------------------------------------
	int currentLife;
	float currentStamina;
	int invincibleTimer;
	int staminaRecoverCoolTime;
	const int kInvincibleTimer = 60;
	const int kStaminaRecoverCoolTime = 150;
	const float kMaxStamina = 600.0f;
	const float kConsumedStamina = 2.0f;
	const float kFirstConsumedStamina = 60.0f;
	const float kRecoverStaminaAmount = 5.0f;

	bool isInvinciblity;
	bool isAlive;
	bool isUpDamage;
	bool isStaminaRecovery;

	// 包含オブジェクト
	// ----------------------------------------------
	Parry parry;
	Bullet bullets[kBulletMax];

	// 描画
	// ----------------------------------------------
	int grHandleCaracter;

};
