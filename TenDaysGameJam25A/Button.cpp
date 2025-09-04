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
	mousePos = {static_cast<float>(mouseX), static_cast<float>(-mouseY)};
}

void Button::CheckHitCursor() {

}

bool Button::IsNone() { return false; }

bool Button::IsHover() { return false; }

bool Button::IsClicked() { return false; }
