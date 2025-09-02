#pragma once
#include "Dlib.h"

class Reaction {
public:
	Reaction();

	void Initialize(int textureHandle, float w, float h);
	void Update();
	void Draw() const;

	void Activate(const Vector2& position, float rotation);
	unsigned int Lerp(unsigned int a, unsigned int b, float rt);
	void SetCamera();

	Transform2D transform;
	Renderer renderer;

	int grHandle;
	float duration;
	float t;

	float width;
	float height;

	bool isActive;
	int activeFrameCount;
	
	unsigned int alpha;
};
