#include "Renderer.h"
#define _USE_MATH_DEFINES
#include <math.h>

Renderer::Renderer() {
	orthoMatrix_ = Matrix3x3::MakeOrthographicMatrix(-640.0f, 360.0f, 640.0f, -360.0f);
	viewportMatrix_ = Matrix3x3::MakeViewportMatrix(0.0f, 0.0f, 1280.0f, 720.0f);
	grHandleInit = Novice::LoadTexture("./Resources/images/box.png");
	UpdateMatrices();
}

void Renderer::SetCamera(const Transform2D& cameraTransform) {
	camera_ = cameraTransform;
	UpdateMatrices();
}

const Transform2D& Renderer::GetCamera() { return camera_; }

void Renderer::UpdateMatrices() {
	Matrix3x3 cameraWorld = camera_.GetWorldMatrix();
	viewMatrix_ = Matrix3x3::Inverse(cameraWorld);
}

Vector2 Renderer::WorldToScreen(const Vector2& worldPos) const {
	Matrix3x3 wvp = viewMatrix_ * orthoMatrix_ * viewportMatrix_;
	return worldPos.Transform(wvp);
}

void Renderer::DrawBox(const Transform2D& transform, float width, float height, float deltaAngle, unsigned int color, FillMode fillMode) const {
	Transform2D t = transform;
	t.rotation = transform.rotation + deltaAngle / 180.0f * static_cast<float>(M_PI);

	// 中心からのオフセット（ローカル座標）
	Vector2 localLeftTop = {-width / 2, -height / 2};
	Vector2 localRightTop = {width / 2, -height / 2};
	Vector2 localLeftBottom = {-width / 2, height / 2};
	Vector2 localRightBottom = {width / 2, height / 2};

	// ワールド行列
	Matrix3x3 worldMatrix = t.GetWorldMatrix();

	// ワールド座標
	Vector2 lt = localLeftTop.Transform(worldMatrix);
	Vector2 rt = localRightTop.Transform(worldMatrix);
	Vector2 lb = localLeftBottom.Transform(worldMatrix);
	Vector2 rb = localRightBottom.Transform(worldMatrix);

	// スクリーン座標に変換
	lt = WorldToScreen(lt);
	rt = WorldToScreen(rt);
	lb = WorldToScreen(lb);
	rb = WorldToScreen(rb);

	if (fillMode == kFillModeSolid) {
		Novice::DrawQuad(
		    static_cast<int>(lt.x), 
			static_cast<int>(lt.y), 
			static_cast<int>(rt.x),
			static_cast<int>(rt.y),
			static_cast<int>(lb.x),
			static_cast<int>(lb.y),
			static_cast<int>(rb.x),
		    static_cast<int>(rb.y),
			0, 0,
			1, 1,
			Novice::LoadTexture("./NoviceResources/white1x1.png"),
			color
		);
	} else {
		Novice::DrawLine(static_cast<int>(lt.x), static_cast<int>(lt.y), static_cast<int>(rt.x), static_cast<int>(rt.y), color);
		Novice::DrawLine(static_cast<int>(rt.x), static_cast<int>(rt.y), static_cast<int>(rb.x), static_cast<int>(rb.y), color);
		Novice::DrawLine(static_cast<int>(rb.x), static_cast<int>(rb.y), static_cast<int>(lb.x), static_cast<int>(lb.y), color);
		Novice::DrawLine(static_cast<int>(lb.x), static_cast<int>(lb.y), static_cast<int>(lt.x), static_cast<int>(lt.y), color);
	}
}

void Renderer::DrawSprite(const Transform2D& transform, float width, float height, float deltaAngle, int textureHandle, unsigned int color) const {

	Transform2D t = transform;
	t.rotation = transform.rotation + deltaAngle / 180.0f * static_cast<float>(M_PI);

	// 中心からのオフセット（ローカル座標）
	Vector2 localLeftTop = {-width / 2, -height / 2};
	Vector2 localRightTop = {width / 2, -height / 2};
	Vector2 localLeftBottom = {-width / 2, height / 2};
	Vector2 localRightBottom = {width / 2, height / 2};

	// ワールド行列
	Matrix3x3 worldMatrix = t.GetWorldMatrix();

	// ワールド座標
	Vector2 lt = localLeftTop.Transform(worldMatrix);
	Vector2 rt = localRightTop.Transform(worldMatrix);
	Vector2 lb = localLeftBottom.Transform(worldMatrix);
	Vector2 rb = localRightBottom.Transform(worldMatrix);

	// スクリーン座標に変換
	lt = WorldToScreen(lt);
	rt = WorldToScreen(rt);
	lb = WorldToScreen(lb);
	rb = WorldToScreen(rb);

	if (textureHandle == -1) {
		Novice::DrawQuad(
			static_cast<int>(lb.x),
			static_cast<int>(lb.y),
			static_cast<int>(rb.x),
			static_cast<int>(rb.y),
		    static_cast<int>(lt.x), 
			static_cast<int>(lt.y),
			static_cast<int>(rt.x), 
			static_cast<int>(rt.y),
		    static_cast<int>(0), 
			static_cast<int>(0), 
			static_cast<int>(width),
			static_cast<int>(height), 
			textureHandle, 
			color
		);
	} else {
		Novice::DrawQuad(
			static_cast<int>(lb.x),
			static_cast<int>(lb.y),
			static_cast<int>(rb.x),
			static_cast<int>(rb.y),
		    static_cast<int>(lt.x), 
			static_cast<int>(lt.y),
			static_cast<int>(rt.x), 
			static_cast<int>(rt.y),
		    static_cast<int>(0), 
			static_cast<int>(0), 
			static_cast<int>(width),
			static_cast<int>(height), 
			textureHandle, 
			color
		);
	}
}

void Renderer::DrawQuad(
    const Transform2D& transform, const Vector2& leftTop, const Vector2& rightTop, const Vector2& leftBottom, const Vector2& rightBottom, float deltaAngle, unsigned int color,
    FillMode fillMode) const {
	Transform2D t = transform;
	t.rotation = transform.rotation + deltaAngle / 180.0f * static_cast<float>(M_PI);

	// ワールド行列
	Matrix3x3 worldMatrix = t.GetWorldMatrix();

	// ワールド座標
	Vector2 lt = leftTop.Transform(worldMatrix);
	Vector2 rt = rightTop.Transform(worldMatrix);
	Vector2 lb = leftBottom.Transform(worldMatrix);
	Vector2 rb = rightBottom.Transform(worldMatrix);

	// スクリーン座標に変換
	lt = WorldToScreen(lt);
	rt = WorldToScreen(rt);
	lb = WorldToScreen(lb);
	rb = WorldToScreen(rb);

	if (fillMode == kFillModeSolid) {
		Novice::DrawQuad(
		    static_cast<int>(lt.x), 
			static_cast<int>(lt.y), 
			static_cast<int>(rt.x),
			static_cast<int>(rt.y),
			static_cast<int>(lb.x),
			static_cast<int>(lb.y),
			static_cast<int>(rb.x),
		    static_cast<int>(rb.y),
			0, 0,
			1, 1,
			Novice::LoadTexture("./NoviceResources/white1x1.png"),
			color
		);
	} else {
		Novice::DrawLine(static_cast<int>(lt.x), static_cast<int>(lt.y), static_cast<int>(rt.x), static_cast<int>(rt.y), color);
		Novice::DrawLine(static_cast<int>(rt.x), static_cast<int>(rt.y), static_cast<int>(rb.x), static_cast<int>(rb.y), color);
		Novice::DrawLine(static_cast<int>(rb.x), static_cast<int>(rb.y), static_cast<int>(lb.x), static_cast<int>(lb.y), color);
		Novice::DrawLine(static_cast<int>(lb.x), static_cast<int>(lb.y), static_cast<int>(lt.x), static_cast<int>(lt.y), color);
	}
}

void Renderer::DrawQuad(
    const Transform2D& transform,
	const Vector2& leftTop,
	const Vector2& rightTop,
	const Vector2& leftBottom,
	const Vector2& rightBottom,
	float srcX, 
	float srcY, 
	float srcW, 
	float srcH, 
	float deltaAngle,
	unsigned int color,
	int textureHandle
) const {
	Transform2D t = transform;
	t.rotation = transform.rotation + deltaAngle / 180.0f * static_cast<float>(M_PI);

	// ワールド行列
	Matrix3x3 worldMatrix = t.GetWorldMatrix();

	// ワールド座標
	Vector2 lt = leftTop.Transform(worldMatrix);
	Vector2 rt = rightTop.Transform(worldMatrix);
	Vector2 lb = leftBottom.Transform(worldMatrix);
	Vector2 rb = rightBottom.Transform(worldMatrix);

	// スクリーン座標に変換
	lt = WorldToScreen(lt);
	rt = WorldToScreen(rt);
	lb = WorldToScreen(lb);
	rb = WorldToScreen(rb);

	Novice::DrawQuad(
	    static_cast<int>(lt.x), 
		static_cast<int>(lt.y),
		static_cast<int>(rt.x), 
		static_cast<int>(rt.y),
		static_cast<int>(lb.x),
		static_cast<int>(lb.y),
		static_cast<int>(rb.x),
		static_cast<int>(rb.y),
	    static_cast<int>(srcX), 
		static_cast<int>(srcY), 
		static_cast<int>(srcW),
		static_cast<int>(srcH), 
		textureHandle, 
		color
	);
}

void Renderer::DrawTriangle(const Transform2D& transform, const Vector2& vertex1, const Vector2& vertex2, const Vector2& vertex3, float deltaAngle, unsigned int color, FillMode fillMode) const {
	Transform2D t = transform;
	t.rotation = transform.rotation + deltaAngle / 180.0f * static_cast<float>(M_PI);

	Matrix3x3 worldMatrix = t.GetWorldMatrix();

	Vector2 v1 = vertex1.Transform(worldMatrix);
	Vector2 v2 = vertex2.Transform(worldMatrix);
	Vector2 v3 = vertex3.Transform(worldMatrix);

	v1 = WorldToScreen(v1);
	v2 = WorldToScreen(v2);
	v3 = WorldToScreen(v3);

	Novice::DrawTriangle(
		static_cast<int>(v1.x),
		static_cast<int>(v1.y),
		static_cast<int>(v2.x),
		static_cast<int>(v2.y),
		static_cast<int>(v3.x), 
		static_cast<int>(v3.y),
		color,
		fillMode
	);
}

void Renderer::DrawEllipse(const Transform2D& transform, const Vector2& radius, const Vector2& deltaPosition, float deltaAngle, unsigned int color, FillMode fillMode) const {
	Vector2 center = WorldToScreen(transform.position + deltaPosition );
	Vector2 radiusScale = transform.scale * radius;
	float angle = transform.rotation + deltaAngle / 180.0f * static_cast<float>(M_PI);

	Novice::DrawEllipse(
		static_cast<int>(center.x),
		static_cast<int>(center.y),
		static_cast<int>(radiusScale.x),
		static_cast<int>(radiusScale.y),
		angle,
		color,
		fillMode
	);
}



