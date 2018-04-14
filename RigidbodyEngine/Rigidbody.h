#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Component.h"

using namespace DirectX;
class Rigidbody : public Component {
public:
	Rigidbody();
	virtual ~Rigidbody();

	bool IsKinematic();
	void SetKinematic(bool isKinematic);
	float GetMass();
	void SetMass(float mass);
	XMVECTOR GetVelocity();
	void SetVelocity(XMVECTOR velocity);

	void AddForce(XMVECTOR* force);
	XMVECTOR GetForceAcceleration();

private:
	bool mKinematic;
	float mMass;
	XMVECTOR mVelocity;
	vector<XMVECTOR*> mForces;
};