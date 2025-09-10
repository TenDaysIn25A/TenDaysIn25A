#pragma once
#include "Dlib.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyHpGauge.h"
#include"Light.h"

enum class Stage1BossAttack {
	MADNESS_TEMPTATION, SQUIDSWIM, FISHBONE, FISHSWIM, FOURWALL, PAPYRUS, LIGHT, TURN, RANDOMFISH,WAVEBLOCK
};

class Stage1Boss {
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
		float width = kBulletNormalWidth;
		float height = kBulletNormalHeight;
		float speed = kBulletNormalSpeed;
		int damage = kBulletNormalDamage;
		unsigned int color = 0xFFFFFFFF;
		BulletType type = BulletType::SHOT;
		int grHandle = Novice::LoadTexture("./Resources/images/box.png");
	};


	// ----------------------------------------------
	// メンバ関数
	// ----------------------------------------------

	Stage1Boss();

	// 根幹
	// ----------------------------------------------

	/// <summary>
	/// 初期化をここに
	/// </summary>
	void Initialize();

	/// <summary>
	/// 弾の初期化
	/// </summary>
	void InitializeBullets(int index, const BulletConfig& bulletConfig);

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
	/// ユウワクノキョウキの攻撃パターン
	/// </summary>
	void AttackMadnessTemptation();

	/// <summary>
	/// アタックイカソウメンの攻撃パターン
	/// </summary>
	void AttackMachingun();

	/// <summary>
	/// アタックフィッシュボーンの攻撃パターン
	/// </summary>
	void AttackFishBone();

	/// <summary>
	/// アタック魚群の攻撃パターン
	/// </summary>
	void AttackFishSwim();

	/// <summary>
	/// アタックパッピの攻撃パターン
	/// </summary>
	void AttackFourWall();

	/// <summary>
	/// 強ランダムの攻撃パターン
	/// </summary>
	void AttackRandomFish();

	/// <summary>
	/// アタックターンの攻撃パターン
	/// </summary>
	void AttackTurn();

	/// <summary>
	/// キラメキノキョウキの攻撃パターン
	/// </summary>
	void AttackLight();

	/// <summary>
	/// ウルトラかっこいい普通の攻撃パターン
	/// </summary>
	void AttackBoneTussle();

	/// <summary>
	/// ウルトラかっこいい普通の攻撃パターン
	/// </summary>
	void AttackScoolOfFish();

	/// <summary>
	/// 特殊攻撃をフェーズごとに選択
	/// </summary>
	void SpecialAttackSelect();

	/// <summary>
	/// 通常攻撃をフェーズごとに選択
	/// </summary>
	void CommonAttackSelect();

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

	/// <summary>
	/// 敵のアニメーションの描画処理
	/// </summary>
	void RoaringCircleUpdate();

	/// <summary>
	/// 敵のアニメーションの描画処理
	/// </summary>
	void RoaringCircleDraw() const;

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
	static constexpr float kBulletNormalSpeed = 16.0f;
	static constexpr float kBulletHighSpeed = 20.0f;
	static constexpr float kBulletNormalWidth = 80.0f;
	static constexpr float kBulletNormalHeight = 160.0f;
	static constexpr int kBulletNormalDamage = 1;
	int grHandleBullet;
	int grHandleBulletFish;
	int grHandleFishBoneTop;
	int grHandleFishBoneBottom;
	int grHandleBigFishBoneBottom;
	int grHandleBigFishBoneTop;
	int grHandleBigWave;
	int grHandleSquid;
	int grHandleBlock;
	int grHandleTwinBlocks;
	int grHandleLight;

	EnemyHpGauge hpGauge;

	Stage1BossAttack attack;
	AttackPhase attackPhase;

	int hp;
	int maxHp;
	float width;
	float height;
	bool isAlive;
	bool isEnd;
	bool isAnger;
	bool isTemptation;
	bool isPhase3Start;
	bool isStartAnimation;

	const unsigned int kDamageColor = 0xAA5555FF;
	const unsigned int kAngerColor = 0xEEEE00FF;
	const unsigned int kTemptationColor = 0xF055F0FF;
	const unsigned int kColor = 0x00EEEEFF;

	int color;

	int specialAttackCounter;

	int shotTimer;
	int shotCounter;

	int exchengePhaseSecondHp;
	int exchengePhaseThirdHp;

	int randomPositionY;

	int returnFishPosY[6];

	int lightAttackTimer;
	const int kLightAttackDefaultTimer = 60;
	static constexpr int kLightMax = 2;
	Light light[kLightMax];

	float meteorShowerCenterPos[64];
	float meteorTheta;

	// 描画
	// 
	int grHandleBox;

	//アニメーションを描画する関数
	Transform2D chochinMouthBottom;
	float chochinMouthBottomWidth;
	float chochinMouthBottomHeight;
	int grHandleChochinMouthBottom0;
	int grHandleChochinMouthBottom1;
	int grHandleChochinMouthBottom2;
	int grHandleChochinMouthBottom3;
	float chochinMouthBottomTheta;

	Transform2D chochinMouthTop;
	float chochinMouthTopWidth;
	float chochinMouthTopHeight;
	int grHandleChochinMouthTop0;
	int grHandleChochinMouthTop1;
	int grHandleChochinMouthTop2;
	int grHandleChochinMouthTop3;
	float chochinMouthTopTheta;
	int chochinAnimationCount;

	Transform2D chochinEies;
	float chochinEiesWidth;
	float chochinEiesHeight;
	int grHandleChochinEies;
	float chochinEiesTheta;
	int chochinEiesRotateTimer;
	const float kChochinEiesOffsetX = 0.0f;
	const float kChochinEiesOffsetY = 320.0f;

	Transform2D chochinLight;
	float chochinLightWidth;
	float chochinLightHeight;
	int grHandleChochinLight0;
	int grHandleChochinLight1;
	int grHandleChochinLight2;
	int grHandleChochinLight3;
	float chochinLightTheta;
	float chochinLightThetaSpeed;
	bool chochinLightIsActive;
	const float kChochinLightOffsetX = -100.0f;
	const float kChochinLightOffsetY = 330.0f;

	float chochinAmplitudeX;
	float chochinAmplitudeY;
	float chochinWavingThetaX;
	float chochinWavingThetaY;
	float chochinThetaSpeed;
	const float kChochinMouthOffsetX = 550.0f;
	const float kChochinMouthOffsetY = -200.0f;

	unsigned int chochinColor;

	float chochinPositionX;
	float chochinVelocityX;
	int chochinAnimTimer;

	static constexpr int kChochinRoaringMax = 64;

	float chochinRoaringRadius[kChochinRoaringMax];
	bool isChochinRoaringVisible[kChochinRoaringMax];

	// 音楽
	// ------------------------------------------------------------------------

	int auHandleRoar; // 咆哮
	bool isPlayedAudioRoar; // 咆哮が再生されたか
	const float auVolumeRoar = 0.3f; // 咆哮の音量

	int auHandleFlash; // 閃光
	const float auVolumeFlash = 0.3f; // 閃光の音量

	int auHandleFlashAttack; // 閃光の攻撃
	const float auVolumeFlashAttack = 0.3f; // 閃光の攻撃の音量

	int auHandleTakeDamage; // ダメージ
	const float auVolumeTakeDamage = 0.05f; // ダメージの音量

	int auHandleBulletDestroy; // 弾の削除

	int auHandleDead; // ボスの沈む音
	int isPlayedAudioDead; // ボスの沈む音が再生されたか
	const float auVolumeDead = 0.5f; // ボスの沈む音の音量
};
