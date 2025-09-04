#include "Button.h"

Button::Button() { Initialize(); }

void Button::Initialize() {
	tweenStepHovered = 0;
	t = 0;
	grHandle = Novice::LoadTexture("./Resources/images/box.png");
	camera.position = {0.0f, 0.0f};
	renderer.SetCamera(camera);
	width = 128.0f;
	height = 32.0f;
	ease = EASE_INOUT_QUAD;

	duration = 0.2f;

	scaleNone = {1.0f, 1.0f};
	scaleHover = {1.4f, 1.4f};
	scaleCliked = {1.4f,0.0f};

	transform.scale = scaleNone;
	state = ButtonState::NONE;
}

void Button::Initialize(int textureHandle, float w, float h) {
	Initialize();
	grHandle = textureHandle;
	width = w;
	height = h;
}

void Button::Update() {
	ButtonState prevState = state;

	state = ButtonState::NONE;
	GetMousePos();
	CheckHitCursor();

	if (state != prevState) {
		t = 0.0f;
	}

	t += 1.0f / 60.0f / duration;
	if (t > 1.0f) {
		t = 1.0f;
	}

	Vector2 nextScale = scaleNone;
	switch (state) {
	case ButtonState::NONE:
		nextScale = scaleNone;
		color = 0x333333FF;
		break;
	case ButtonState::HOVER:
		if (nextState == ButtonState::CLICKED) {
			nextScale = scaleCliked;
		} else {
			nextScale = scaleHover;
		}
		color = 0xAAAAAAFF;
		break;
	case ButtonState::CLICKED:
		nextScale = scaleCliked;
		break;
	}

	float eased = Tweening::Easing(t, ease);
	Vector2 startScale = transform.scale;
	Vector2 newScale = startScale + (nextScale - startScale) * eased;

	if (nextState == ButtonState::CLICKED) {
		color = 0xFFFFFFFF;
		transform.scale = newScale;

		if (t >= 1.0f) {
			state = ButtonState::CLICKED;
			nextState = ButtonState::NONE;
			t = 0.0f;
		}
	} else {
		transform.scale = newScale;
	}
}

void Button::Draw() const {
	Novice::ScreenPrintf(0, 0, "%f", mousePos.x);
	Novice::ScreenPrintf(0, 20, "%f", mousePos.y);

	renderer.DrawSprite(transform, width, height, 0.0f, grHandle, color);
}

void Button::GetMousePos() {
	int mouseX;
	int mouseY;
	Novice::GetMousePosition(&mouseX, &mouseY);
	mousePos = {static_cast<float>(mouseX) - 640.0f, static_cast<float>(-mouseY) + 360.0f};
}

void Button::CheckHitCursor() {

	if (Collision::BoxToPoint(transform.position, mousePos, width, height)) {
		if (Novice::IsTriggerMouse(0)) {
			nextState = ButtonState::CLICKED;
		} else {
			state = ButtonState::HOVER;
		}
	} else {
		state = ButtonState::NONE;
	}
}

bool Button::IsNone() { return (state == ButtonState::NONE); }

bool Button::IsHover() { return (state == ButtonState::HOVER); }

bool Button::IsClicked() { return (state == ButtonState::CLICKED); }
