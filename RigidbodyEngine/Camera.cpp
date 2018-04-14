#include "Camera.h"

Camera::Camera()
	: Component("Camera") {
	mPosition = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	mTarget = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
	mUp = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	mRight = XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f);
	SetProjection(XM_PIDIV4, 1920 / 1080.0f, 0.01f, 1000.0f);
}

Camera::~Camera() {

}

XMMATRIX Camera::View() {
	return XMMatrixLookAtLH(mPosition, mTarget, mUp);
}

XMMATRIX Camera::Projection() {
	return mProjection;
}

void Camera::SetProjection(float fovAngleY, float aspectRatio, float nearZ, float farZ) {
	mProjection = XMMatrixPerspectiveFovRH(fovAngleY, aspectRatio, nearZ, farZ);
}

XMVECTOR Camera::Position() {
	return mPosition;
}

void Camera::SetPosition(XMVECTOR positionVector) {
	mPosition = positionVector;
}

XMVECTOR Camera::Target() {
	return mTarget;
}

void Camera::SetTarget(XMVECTOR targetVector) {
	mTarget = targetVector;
}

XMVECTOR Camera::Up() {
	return mUp;
}

void Camera::SetUp(XMVECTOR upVector) {
	mUp = upVector;
}

XMVECTOR Camera::Right() {
	return mRight;
}

void Camera::SetRight(XMVECTOR rightVector) {
	mRight = rightVector;
}

XMVECTOR Camera::Normal() {
	return XMVector3Normalize(mTarget - mPosition);
}

void Camera::Translate(float x, float y, float z) {
	XMVECTOR transVec = XMVectorSet(x, y, z, 0);
	mPosition += transVec;
	mTarget += transVec;
}

void Camera::Translate(XMVECTOR translation) {
	mPosition += translation;
	mTarget += translation;
}

void Camera::Rotate(float x, float y, float z) {
	//mTarget;
	//mUp;
	//mRight;
}