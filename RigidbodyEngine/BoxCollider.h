#pragma once
#include "Collider.h"

class BoxCollider : public Collider {
public:

	BoxCollider();
	BoxCollider(float w, float h, float d);
	virtual ~BoxCollider();

	void GeneratePoints(XMVECTOR origin);

private:
	float mWidth;
	float mHeight;
	float mDepth;
};