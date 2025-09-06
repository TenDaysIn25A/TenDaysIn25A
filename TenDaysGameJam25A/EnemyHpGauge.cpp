#include "EnemyHpGauge.h"

EnemyHpGauge::EnemyHpGauge() { Initialize(); };

void EnemyHpGauge::Initialize(){
	maxHp = 100;
	hp = 100;
	width = 500;
	height = 40;
	gaugeFramePixel = 4.0f;
	positionXMisalignment = 0.0f;
	transform.position = {0.0,240.0f};
	color = kColor;
	isVisible = false;
	isBackGroundVisible = false;
}

void EnemyHpGauge::CreateHpGauge(const Vector2& position, int startHp, int setMaxHp, float setWidth, float setHeight, unsigned int setColor, bool setBackGroundVisible) {
	hp = startHp;
	maxHp = setMaxHp;
	width = setWidth;
	height = setHeight;
	transform.position = position;

	isBackGroundVisible = setBackGroundVisible;
	color = setColor;
	isVisible = true;
}

void EnemyHpGauge::Destory(){
	isVisible = false;
}

void EnemyHpGauge::Update(){
}

void EnemyHpGauge::Draw() const{
	if (isBackGroundVisible) {
		renderer.DrawBox(transform, width, height, 0.0f, kBackGrroundColor, kFillModeSolid);
	}

	if (hp > 0) {
		renderer.DrawQuad(
			transform, {-((width - (gaugeFramePixel * 2.0f)) / 2.0f),((height) / 2.0f) - gaugeFramePixel }, { (((width - (gaugeFramePixel * 2.0f)) / maxHp) * hp) - ((width - (gaugeFramePixel * 2.0f)) / 2.0f),(height / 2.0f) - gaugeFramePixel },
			{ -((width - (gaugeFramePixel * 2.0f)) / 2.0f),-(height / 2.0f) + gaugeFramePixel }, { (((width - (gaugeFramePixel * 2.0f)) / maxHp) * hp) - ((width - (gaugeFramePixel * 2.0f)) / 2.0f),-(height / 2.0f) + gaugeFramePixel}, 0.0f, color, kFillModeSolid);
	}
}

void EnemyHpGauge::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void EnemyHpGauge::ReferenceHp(int setHp, int setMaxHp){
	hp = setHp;
	maxHp = setMaxHp;
}


