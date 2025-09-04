#include "Button.h"

Button::Button() { Initialize(); }

void Button::Initialize() {
	tweenStepHovered = 0;
	t = 0;
}

void Button::Initialize(int textureHandle, float w, float h) {
	Initialize();
	grHandle = textureHandle;
	width = w;
	height = h;
}

void Button::Update() {
	GetMousePos();
	CheckHitCursor();
}

void Button::Draw() const {
	Novice::ScreenPrintf(0, 0, "%f", mousePos.x);
	Novice::ScreenPrintf(0, 20, "%f", mousePos.y);
}

void Button::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Button::GetMousePos() {
	int mouseX;
	int mouseY;
	Novice::GetMousePosition(&mouseX, &mouseY);
	mousePos = {static_cast<float>(mouseX) - 640.0f, static_cast<float>(-mouseY) + 360.0f};
}

void Button::CheckHitCursor() {

	if (Collision::BoxToPoint(transform.position, mousePos, width, height)) {
		if (Novice::IsTriggerMouse(0)) {
			state = ButtonState::CLICKED;
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
