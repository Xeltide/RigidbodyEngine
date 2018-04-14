#pragma once
#include <DirectXMath.h>
#include "Component.h"

using namespace DirectX;
class Transform : public Component {
public:
	Transform();
	virtual ~Transform() = default;

	void Translate(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);
	XMMATRIX EvaluateTransform();

	XMVECTOR GetOrigin();
	void SetOrigin(XMVECTOR origin);

private:
	XMMATRIX mPosition;
	XMMATRIX mRotation;
	XMMATRIX mScale;
};