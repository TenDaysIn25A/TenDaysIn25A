#pragma once
#include "Dlib.h"
#include "Parry.h"
#include "Bullet.h"
#include "Reaction.h"
#include"backGround.h"

enum class ShotType { MACHINEGUN, SHOTGUN };

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

	void MachinGunBullet();

	void ShotGunBullet();

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
	DrawEffects effect; // エフェクト描画ライブラリをこれで使えるようにしてください。
	Reaction miss;
	Reaction nice;
	Reaction just;
	BackGround backGround;
	ControlSystem controler;

	// プレイヤープロパティ
	// ----------------------------------------------
	Transform2D transform;

	Transform2D leftTop;
	Transform2D rightTop;
	Transform2D leftBottom;
	Transform2D rightBottom;
	ShotType shotType;


	float speed;
	Vector2 direction;
	Vector2 velocity;

	float width;
	float height;

	static constexpr int kBulletMax = 64;

	int shotTimer;
	int isShot[kBulletMax];
	int shotCoolTime;
	int bulletPattern;
	const int kUpedShotCoolTime = 4;
	const int kDefaultShotCoolTime = 10;

	int magazine;
	const int kMagazineSize = 5;
	int pelletAmount;
	const int kPelletMaxAmount = 8;

	const int kParryTimer = 2;
	const int kUpedDamage = 2;
	const int kDefaultDamage = 2;
	int damageUpTime;



	static constexpr int kMaxLife = 5;
	Transform2D life[kMaxLife];
	const float lifeWidth = 50.0f;
	const float lifeHeight = 50.0f;
	int grhandleLife;

	float hitBoxWidth;
	float hitBoxHeight;

	// ステータス
	// ----------------------------------------------
	int currentLife;
	int invincibleTimer;
	const int kInvincibleTimer = 60;
	const float kRecoverStaminaAmount = 5.0f;

	bool isInvinciblity;
	bool isAlive;
	bool isUpDamage;
	bool isStaminaRecovery;
	bool isBlackHole;
	Vector2 blackHolePos;

	// 包含オブジェクト
	// ----------------------------------------------
	Parry parry;
	Bullet bullets[kBulletMax];

	// 描画
	// ----------------------------------------------
	int grHandleCaracterDimOne;
	int grHandleCaracterDimTwo;

	// 音楽
	// ----------------------------------------------
	int auHandleShot;
	const float auVolumeShot = 0.05f;
	int auHandleParry;
	int auHandleJustParry;
	int auHandleTakeDamage;
	const float auVolumeTakeDamage = 0.1f;
};
