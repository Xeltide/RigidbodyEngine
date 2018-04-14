#include "BoxCollider.h"

BoxCollider::BoxCollider()
	: Collider(string("BoxCollider")) {
	mNumPoints = 8;
	mWidth = 1.0f;
	mHeight = 1.0f;
	mDepth = 1.0f;
}

BoxCollider::BoxCollider(float w, float h, float d)
	: Collider(string("BoxCollider")) {
	mNumPoints = 8;
	mWidth = w;
	mHeight = h;
	mDepth = d;
}

BoxCollider::~BoxCollider() {

}

void BoxCollider::GeneratePoints(XMVECTOR origin) {
	float wOff = mWidth / 2;
	float hOff = mHeight / 2;
	float dOff = mDepth / 2;
	float x = XMVectorGetX(origin);
	float y = XMVectorGetY(origin);
	float z = XMVectorGetZ(origin);

	XMVECTOR* p1 = new XMVECTOR();
	XMVECTOR* p2 = new XMVECTOR();
	XMVECTOR* p3 = new XMVECTOR();
	XMVECTOR* p4 = new XMVECTOR();
	XMVECTOR* p5 = new XMVECTOR();
	XMVECTOR* p6 = new XMVECTOR();
	XMVECTOR* p7 = new XMVECTOR();
	XMVECTOR* p8 = new XMVECTOR();

	*p1 = XMVectorSet(x - wOff, y + hOff, z + dOff, 0.0f);
	*p2 = XMVectorSet(x - wOff, y - hOff, z + dOff, 0.0f);
	*p3 = XMVectorSet(x - wOff, y + hOff, z - dOff, 0.0f);
	*p4 = XMVectorSet(x - wOff, y - hOff, z - dOff, 0.0f);
	*p5 = XMVectorSet(x + wOff, y + hOff, z + dOff, 0.0f);
	*p6 = XMVectorSet(x + wOff, y - hOff, z + dOff, 0.0f);
	*p7 = XMVectorSet(x + wOff, y + hOff, z - dOff, 0.0f);
	*p8 = XMVectorSet(x + wOff, y - hOff, z - dOff, 0.0f);

	mPoints.push_back(p1);
	mPoints.push_back(p2);
	mPoints.push_back(p3);
	mPoints.push_back(p4);
	mPoints.push_back(p5);
	mPoints.push_back(p6);
	mPoints.push_back(p7);
	mPoints.push_back(p8);
}