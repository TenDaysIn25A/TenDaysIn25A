#pragma once
#include "Dlib.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyHpGauge.h"

enum class Stage2BossAttack {
	NORMAL,ALL_WALL,BLACK_HOLE,
};

class Stage2Boss {
public:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="speed"></param>
	/// <param name="damage"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="color"></param>
	struct BulletConfig {
		float speed = kBulletNormalSpeed;
		float width = kBulletNormalWidth;
		float height = kBulletNormalHeight;
		int damage = kBulletNormalDamage;
		unsigned int color = 0xFFFFFFFF;
		BulletType type = BulletType::SHOT;
		int grHandle = Novice::LoadTexture("./Resources/images/box.png");
	};

	// ----------------------------------------------
	// メンバ関数
	// ----------------------------------------------

	Stage2Boss();

	// 根幹
	// ----------------------------------------------

	/// <summary>
	/// 初期化をここに
	/// </summary>
	void Initialize();

	/// <summary>
	/// 弾の初期化
	/// </summary>
	void InitializeBullets(int index ,const BulletConfig& bulletConfig);

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
	/// 壁/ノーツを発射する
	/// </summary>
	void Shot();

	/// <summary>
	/// 敵にダメージを与える
	/// </summary>
	void TakeDamage(int damage);

	/// <summary>
	/// 敵を倒す
	/// </summary>
	void Destory();

	// 機能
	// ----------------------------------------------

	/// <summary>
	/// 特殊攻撃をフェーズごとに選択
	/// </summary>
	void SpecialAttackSelect();

	/// <summary>
	/// 通常攻撃をフェーズごとに選択
	/// </summary>
	void CommonAttackSelect();

	/// <summary>
	/// アタックノーマルの攻撃パターン
	/// </summary>
	void AttackNormal();

	/// <summary>
	/// 全壁攻撃
	/// </summary>
	void AttackAllWall();

	/// <summary>
	/// ブラックホール攻撃
	/// </summary>
	void AttackBlackHole();

private:
	/// <summary>
	/// アニメーションの初期化
	/// </summary>
	void AnimInitialize();

	/// <summary>
	/// 敵のアニメーションを実行する
	/// </summary>
	void AnimUpdate();

	/// <summary>
	/// 敵のアニメーションの描画処理
	/// </summary>
	void AnimDraw() const;

	public:
	// ----------------------------------------------
	// メンバ変数
	// ----------------------------------------------

	// システム
	// ----------------------------------------------
	Renderer renderer;  // 描画ライブラリをこれで使えるようにしてください。
	Input input;        // 入力ライブラリをこれで使えるようにしてください。
	DrawEffects effect; // エフェクト描画ライブラリをこれで使えるようにしてください。

	// エネミープロパティ
	// ----------------------------------------------

	Transform2D transform; // positionとか宣言しなくてええんやで

	float speed;
	Vector2 direction;
	Vector2 velocity;

	// 弾
	// ----------------------------------------------
	static constexpr int kBulletMax = 64;
	Bullet bullets[kBulletMax];
	static constexpr float kBulletNormalSpeed = 10.0f;
	static constexpr float kBulletHighSpeed = 15.0f;
	static constexpr float kBulletNormalWidth = 80.0f;
	static constexpr float kBulletNormalHeight = 160.0f;
	static constexpr int kBulletNormalDamage = 1;
	int grHandleBullet;

	EnemyHpGauge hpGauge;

	Stage2BossAttack attack;
	AttackPhase attackPhase;

	//衛星軌道
	Transform2D newSatellite;
	float satelliteRotateTheta;
	bool isFusion;

	//ブラックホール
	Transform2D blackHole;
	float blackHoleWidth;
	float blackHoleHeight;
	float gravityAreaWidth;
	float gravityAreaHeight;
	int blackHolePhase;
	int barrageTimer;

	int hp;
	int maxHp;
	float width;
	float height;
	bool isAlive;

	const unsigned int kDamageColor = 0xAA5555FF;
	const unsigned int kColor = 0xAA00CCFF;
	int color;

	int shotTimer;
	int shotCounter;

	static constexpr int kExchengePhaseThirdHp = 300;
	static constexpr int kExchengePhaseSecondHp = 600;

	// 描画
	// 
	int grHandleBox;
};
