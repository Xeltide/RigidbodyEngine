#include "Collider.h"

Collider::Collider(string name)
	: Component(name) {

}

Collider::~Collider() {

}

void Collider::CalculateAABB() {
	XMFLOAT3 minPoint = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	XMFLOAT3 maxPoint = XMFLOAT3(FLT_MIN, FLT_MIN, FLT_MIN);

	for (unsigned int i = 0; i < mNumPoints; i++) {
		// Set minimum
		minPoint.x = std::min(minPoint.x, XMVectorGetX(*mPoints[i]));
		minPoint.y = std::min(minPoint.y, XMVectorGetY(*mPoints[i]));
		minPoint.z = std::min(minPoint.z, XMVectorGetZ(*mPoints[i]));
		// Set maximum
		maxPoint.x = std::max(maxPoint.x, XMVectorGetX(*mPoints[i]));
		maxPoint.y = std::max(maxPoint.y, XMVectorGetY(*mPoints[i]));
		maxPoint.z = std::max(maxPoint.z, XMVectorGetZ(*mPoints[i]));
	}

	mBoundingBox.MinPoint = XMVectorSet(minPoint.x, minPoint.y, minPoint.z, 0.0f);
	mBoundingBox.MaxPoint = XMVectorSet(maxPoint.x, maxPoint.y, maxPoint.z, 0.0f);
}

Collider::AABB Collider::GetBoundingBox() {
	return mBoundingBox;
}