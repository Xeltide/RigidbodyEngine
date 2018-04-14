#include "Transform.h"

Transform::Transform()
	: Component("Transform") {
	mPosition = XMMatrixIdentity();
	mRotation = XMMatrixIdentity();
	mScale = XMMatrixIdentity();
}

void Transform::Translate(float x, float y, float z) {
	mPosition = mPosition * XMMatrixTranslation(x, y, z);
}

void Transform::Rotate(float x, float y, float z) {
	mRotation = mRotation * XMMatrixRotationX(x) * XMMatrixRotationY(y) * XMMatrixRotationZ(z);
}

void Transform::Scale(float x, float y, float z) {
	mScale = mScale * XMMatrixScaling(x, y, z);
}

XMMATRIX Transform::EvaluateTransform() {
	return mRotation * mScale * mPosition;
}

XMVECTOR Transform::GetOrigin() {
	return mPosition.r[3];
}

void Transform::SetOrigin(XMVECTOR origin) {
	mPosition.r[3] = origin;
}