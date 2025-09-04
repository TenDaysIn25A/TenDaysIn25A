#pragma once
#include "Dlib.h"
#include "Bullet.h"
#include "Enemy.h"

enum class Stage4BossAttack {
	WALL, MACHINGUN, TUNNEL, ALL_WALL,FOURWALL
};

class Stage4Boss {
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
		unsigned int color = 0xFFFFFFAA;
		int grHandle = Novice::LoadTexture("./Resources/images/box.png");
	};


	// ----------------------------------------------
	// メンバ関数
	// ----------------------------------------------

	Stage4Boss();

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
	/// アタックウォールの攻撃パターン
	/// </summary>
	void AttackWall();

	/// <summary>
	/// アタックマシンガンの攻撃パターン
	/// </summary>
	void AttackMachingun();

	/// <summary>
	/// アタック連打の攻撃パターン
	/// </summary>
	void AttackFishBone();

	/// <summary>
	/// アタックオールウォールの攻撃パターン
	/// </summary>
	void AttackAllWall();

	/// <summary>
	/// アタックオールウォールの攻撃パターン
	/// </summary>
	void AttackFourWall();

	/// <summary>
	/// 特殊攻撃をフェーズごとに選択
	/// </summary>
	void SpecialAttackSelect();

	/// <summary>
	/// 通常攻撃をフェーズごとに選択
	/// </summary>
	void CommonAttackSelect();

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

	Stage4BossAttack attack;
	AttackPhase attackPhase;

	int hp;
	int maxHp;
	float width;
	float height;
	bool isAlive;

	const unsigned int kDamageColor = 0xAA5555FF;
	const unsigned int kColor = 0xAAFFFFFF;
	int color;

	int attackPositionX;

	int shotTimer;
	int shotCounter;

	int exchengePhaseSecondHp;
	int exchengePhaseThirdHp;

	int randomPositionY;

	// 描画
	// 
	int grHandleCaracter;
};
