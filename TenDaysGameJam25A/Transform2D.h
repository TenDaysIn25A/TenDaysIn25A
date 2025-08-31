#pragma once
#include "Vector2.h"
#include "Matrix3x3.h"

/// <summary>
/// 移動・回転・スケールを管理
/// </summary>
class Transform2D {
public:
	Vector2 position;
	float rotation;
	Vector2 scale_;
	
public:
	Transform2D();
	~Transform2D() = default;
	
	/// <summary>
	/// 平行移動に変化量分加算します。
	/// </summary>
	/// <param name="deltaVelocity"></param>
	void Translate(const Vector2& deltaVelocity);

	/// <summary>
	/// 回転に変化量分加算します。
	/// </summary>
	/// <param name="deltaAngle"></param>
	void Rotate(float deltaAngle);

	/// <summary>
	/// スケールに変化量分加算します。
	/// </summary>
	/// <param name="deltaScale"></param>
	void Scale(const Vector2& deltaScale);

	Matrix3x3 GetWorldMatrix() const;
};
