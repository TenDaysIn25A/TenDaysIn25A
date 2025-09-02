#include "Reaction.h"

Reaction::Reaction() { isActive = false; }

void Reaction::Initialize(int textureHandle, float w, float h) { 
	grHandle = textureHandle;
	isActive = false;
	activeFrameCount = 0;
	duration = 0.5f;
	alpha = 0x00000000;
	t = 0.0f;
	width = w;
	height = h;
}

void Reaction::Update() {
	if (!isActive) {
		return;
	}

	t += 1.0f / 60.0f / duration;

	if (t >= 1.0f) {
		t = 1.0f;
		isActive = false;
	}

	
	alpha = Lerp(0x00000000u, 0x000000FFu, t);
}

void Reaction::Draw() const {
	if (!isActive) {
		return;
	}

	renderer.DrawSprite(transform, width, height, 0.0f, grHandle, 0xFFFFFFFF - alpha);
}

void Reaction::Activate(const Vector2& position, float rotation) { 
	isActive = true; 
	duration = 0.5f;
	alpha = 0x00000000;
	t = 0.0f;
	transform.position = position;
	transform.rotation = rotation;
}

unsigned int Reaction::Lerp(unsigned int a, unsigned int b, float rt) { return static_cast<unsigned int>(a + (b - a) * rt); }

