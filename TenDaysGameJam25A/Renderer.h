#pragma once
#include "Matrix3x3.h"
//#include "UpgradeManager.h"
#include "Transform2D.h"
#include "Vector2.h"
#include <Novice.h>

class Renderer {
public:
	Renderer();
	~Renderer() = default;

	// カメラ設定
	void SetCamera(const Transform2D& cameraTransform);
	const Transform2D& GetCamera();

	void UpdateMatrices();

	/// <summary>
	/// 中心座標を基に描画
	/// </summary>
	/// <param name="transform">中心点</param>
	/// <param name="width">横幅</param>
	/// <param name="height">縦幅</param>
	/// <param name="color">色</param>
	/// <param name="fillMode"></param>
	void DrawBox(const Transform2D& transform, float width, float height, float deltaAngle, unsigned int color, FillMode fillMode) const;

	void DrawSprite(const Transform2D& transform, float width, float height, float deltaAngle, int textureHandle, unsigned int color) const;

	void DrawQuad(
	    const Transform2D& transform, const Vector2& leftTop, const Vector2& rightTop, const Vector2& leftBottom, const Vector2& rightBottom, float deltaAngle, unsigned int color,
	    FillMode fillMode) const;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="transform"></param>
	/// <param name="leftTop">左上</param>
	/// <param name="rightTop">右上</param>
	/// <param name="leftBottom">左下</param>
	/// <param name="rightBottom">右下</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="deltaAngle">最初からつけたい角度</param>
	/// <param name="color"></param>
	/// <param name="textureHandle"></param>
	void DrawQuad(
	    const Transform2D& transform, const Vector2& leftTop, const Vector2& rightTop, const Vector2& leftBottom, const Vector2& rightBottom, float srcX, float srcY, float srcW, float srcH,
	    float deltaAngle,
	    unsigned int color, int textureHandle) const;

	void DrawTriangle(const Transform2D& transform, const Vector2& vertex1, const Vector2& vertex2, const Vector2& vertex3, float deltaAngle, unsigned int color, FillMode fillMode) const;

	void DrawEllipse(const Transform2D& transform, const Vector2& radius, const Vector2& deltaPosition, float deltaAngle, unsigned int color, FillMode fillMode) const;

private:
	Transform2D camera_;
	Matrix3x3 viewMatrix_;
	Matrix3x3 orthoMatrix_;
	Matrix3x3 viewportMatrix_;

	int grHandleInit;

	Vector2 WorldToScreen(const Vector2& worldPos) const;
};
