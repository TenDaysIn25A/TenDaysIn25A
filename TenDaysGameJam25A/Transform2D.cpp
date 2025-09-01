#include "Transform2D.h"
#define _USE_MATH_DEFINES
#include <math.h>

Transform2D::Transform2D() {
	position = {0.0f, 0.0f};
	rotation = 0.0f;
	scale = {1.0f, 1.0f};
}

void Transform2D::Translate(const Vector2& delta) { position += delta; }

void Transform2D::Rotate(float deltaAngle) { rotation += deltaAngle / 180.0f * static_cast<float>(M_PI); }

void Transform2D::Scale(const Vector2& deltaScale) { scale += deltaScale; }

Matrix3x3 Transform2D::GetWorldMatrix() const { return Matrix3x3::MakeAffineMatrix(scale, rotation, position); }
