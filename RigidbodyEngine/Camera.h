#pragma once
#include <DirectXMath.h>
#include "Component.h"

using namespace DirectX;
class Camera : public Component {
public:

	Camera();
	virtual ~Camera();

	XMMATRIX View();
	XMMATRIX Projection();
	void SetProjection(float fovAngleY, float aspectRatio, float nearZ, float farZ);

	XMVECTOR Position();
	void SetPosition(XMVECTOR positionVector);
	XMVECTOR Target();
	void SetTarget(XMVECTOR targetVector);
	XMVECTOR Up();
	void SetUp(XMVECTOR upVector);
	XMVECTOR Right();
	void SetRight(XMVECTOR rightVector);
	XMVECTOR Normal();

	void Translate(float x, float y, float z);
	void Translate(XMVECTOR translation);
	void Rotate(float x, float y, float z);

private:
	
	XMVECTOR mPosition;
	XMVECTOR mTarget;
	XMVECTOR mUp;
	XMVECTOR mRight;

	XMMATRIX mProjection;
};