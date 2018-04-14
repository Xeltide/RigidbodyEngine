#pragma once
#include <DirectXMath.h>
#include <algorithm>
#include <vector>
#include "Component.h"

using namespace DirectX;
class Collider : public Component {
public:
	typedef struct AABB {
		XMVECTOR MinPoint;
		XMVECTOR MaxPoint;
	};

	Collider(string name);
	virtual ~Collider();

	void CalculateAABB();
	AABB GetBoundingBox();

protected:
	unsigned int mNumPoints;
	vector<XMVECTOR*> mPoints;
	AABB mBoundingBox;
};