#include "Light.h"

Light::Light() { Initialize(); };

void Light::Initialize() {

	transform.position = { 0.0f,300.0f };
	radius = { 50.0f ,50.0f};
}

void Light::Update() {





}


/// <summary>
/// 
/// </summary>
/// <param name="弾の座標"></param>
/// <param name="弾の幅"></param>
/// <param name="弾の高さ"></param>
/// <param name="影にいるか判定したいオブジェクト"></param>
/// <returns></returns>
int Light::isPlayerInTheShadow(Transform2D& enemyBullet, float enemyBulletWidth, float enemyBulletHeight, Vector2& target) {

	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftBottom;
	Vector2 rightBottom;

	leftTop.x = enemyBullet.position.x - enemyBulletWidth / 2.0f;
	leftTop.y = enemyBullet.position.y + enemyBulletHeight / 2.0f;

	rightTop.x = enemyBullet.position.x + enemyBulletWidth / 2.0f;
	rightTop.y = enemyBullet.position.y + enemyBulletHeight / 2.0f;

	leftBottom.x = enemyBullet.position.x - enemyBulletWidth / 2.0f;
	leftBottom.y = enemyBullet.position.y - enemyBulletHeight / 2.0f;

	rightBottom.x = enemyBullet.position.x + enemyBulletWidth / 2.0f;
	rightBottom.y = enemyBullet.position.y - enemyBulletHeight / 2.0f;

	if (leftTop.y >= transform.position.y && leftBottom.y <= transform.position.y) {

		if (isTargetLeftOfLight(rightTop, target) && isTargetRightOfLight(rightBottom, target)) {

			return true;
		}
	} else if(leftTop.y < transform.position.y){

		if (isTargetLeftOfLight(leftTop, target) && isTargetRightOfLight(rightBottom, target)) {

			return true;
		}
	} else {

		if (isTargetLeftOfLight(rightTop, target) && isTargetRightOfLight(leftBottom, target)) {

			return true;
		}

	}

	return false;
}

int Light::isTargetLeftOfLight(Vector2& posA,Vector2& target) {

	cross = Vector2::Orientation(transform.position, posA, target);

	if (cross < 0.0f) {
		return true;
	}

	return false;

}

int Light::isTargetRightOfLight(Vector2& posB, Vector2& target) {

	cross = Vector2::Orientation(transform.position, posB, target);

	if (cross > 0.0f) {
		return true;
	}

	return false;

}

void Light::Draw()const {

}

//影の描画
void Light::DrawShadow(Transform2D& enemyBullet, float enemyBulletWidth, float enemyBulletHeight) {

	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftBottom;
	Vector2 rightBottom;

	leftTop.x = enemyBullet.position.x - enemyBulletWidth / 2.0f;
	leftTop.y = enemyBullet.position.y + enemyBulletHeight / 2.0f;

	rightTop.x = enemyBullet.position.x + enemyBulletWidth / 2.0f;
	rightTop.y = enemyBullet.position.y + enemyBulletHeight / 2.0f;

	leftBottom.x = enemyBullet.position.x - enemyBulletWidth / 2.0f;
	leftBottom.y = enemyBullet.position.y - enemyBulletHeight / 2.0f;

	rightBottom.x = enemyBullet.position.x + enemyBulletWidth / 2.0f;
	rightBottom.y = enemyBullet.position.y - enemyBulletHeight / 2.0f;

	if (leftTop.y >= transform.position.y && leftBottom.y <= transform.position.y) {

		Vector2 lightToRightTop;
		Vector2 lightToRightBottom;

	} else if (leftTop.y < transform.position.y) {

	} else {

	}
}