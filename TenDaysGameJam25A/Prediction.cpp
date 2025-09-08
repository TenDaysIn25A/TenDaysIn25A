#include "Prediction.h"

Prediction::Prediction() { Initialize(); }

void Prediction::Initialize(){
	width = 320.0f;
	height = 480.0f;
	isVisible = true;

	color = kColor;

	transform.position = { 640.0f - (width / 2.0f), 0.0f };
	transform.rotation = 0.0f;
	transform.scale = { 1.0f, 1.0f };

	timer = 0;
	timerMax = 0;
	type = PredictionType::Charge;

	grHandleBox = Novice::LoadTexture("./Resources/images/box.png");
}

void Prediction::UpDate(){
	if (!isVisible) {
		return;
	}

	

	switch (type){
	case PredictionType::Charge:
		height = beforeHeight * (1.0f - easing.Easing(((100.0f / static_cast<float>(timerMax)) * (static_cast<float>(timer) / 100.0f)), EASE_OUT_QUAD));

		if (timer <= timerMax - 10) {
			color = colorMath.RGBCreator(
				colorMath.RGBPickUp(kColor,PickUpColor::PICK_UP_RED),
				colorMath.RGBPickUp(kColor, PickUpColor::PICK_UP_GREEN),
				colorMath.RGBPickUp(kColor, PickUpColor::PICK_UP_BLUE),
				static_cast <int>(0xAA * ((100.0f / static_cast<float>(timerMax - 10.0f)) * (static_cast<float>(timer) / 100.0f))));
		} else {
			color = colorMath.RGBCreator(
				colorMath.RGBPickUp(kColor, PickUpColor::PICK_UP_RED),
				colorMath.RGBPickUp(kColor, PickUpColor::PICK_UP_GREEN),
				colorMath.RGBPickUp(kColor, PickUpColor::PICK_UP_BLUE) ,
				 static_cast<int>(0xAA * (1.0f - (100.0f / static_cast<float>(10)) * (static_cast<float>(timerMax - timer) / 100.0f))));
		}

		break;
	case PredictionType::Diffusion:
		break;
	}


	if (timer >= timerMax) {
		isVisible = false;
	}

	timer++;
}

void Prediction::Draw()const{
	if (!isVisible) {
		return;
	}

	if (currentDimension == DimensionState::TWO) {
		renderer.DrawSprite(transform, width, beforeHeight, 0.0f, grHandleBox, color);

		renderer.DrawBox(transform, width + 1.0f, beforeHeight, 0.0f, kColor, kFillModeWireFrame);
		renderer.DrawBox(transform, width + 1.0f, height, 0.0f, kColor, kFillModeWireFrame);
		renderer.DrawBox(transform, width + 1.0f, height * 2.0f, 0.0f, kColor, kFillModeWireFrame);
	}else{
		Transform2D t = transform;
		t.position.y = 0.0f;
		renderer.DrawSprite(t, width, beforeHeight, 0.0f, grHandleBox, color);

		renderer.DrawBox(t, width + 1.0f, beforeHeight, 0.0f, kColor, kFillModeWireFrame);
		renderer.DrawBox(t, width + 1.0f, height, 0.0f, kColor, kFillModeWireFrame);
		renderer.DrawBox(t, width + 1.0f, height * 2.0f, 0.0f, kColor, kFillModeWireFrame);
	}
}

void Prediction::LineCharge(const Vector2& position, float setWidth, float setHeight, int setTimerMax){
	transform.position = position;
	transform.position.x = 0.0f;
	width = setWidth;
	beforeHeight = setHeight;
	height = setHeight;
	timerMax = setTimerMax;
	
	timer = 0;
	isVisible = true;
}
