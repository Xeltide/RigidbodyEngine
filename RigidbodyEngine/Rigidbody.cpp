#include "Rigidbody.h"

Rigidbody::Rigidbody()
	: Component(string("Rigidbody")) {
	mVelocity = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	mKinematic = false;
	mMass = 1.0f;
}

Rigidbody::~Rigidbody() {
	for (auto force = mForces.begin(); force != mForces.end(); force++) {
		delete *force;
	}
}

bool Rigidbody::IsKinematic() {
	return mKinematic;
}

void Rigidbody::SetKinematic(bool isKinematic) {
	mKinematic = isKinematic;
}

float Rigidbody::GetMass() {
	return mMass;
}

void Rigidbody::SetMass(float mass) {
	mMass = mass;
}

XMVECTOR Rigidbody::GetVelocity() {
	return mVelocity;
}

void Rigidbody::SetVelocity(XMVECTOR velocity) {
	mVelocity = velocity;
}

void Rigidbody::AddForce(XMVECTOR* force) {
	mForces.push_back(force);
}

XMVECTOR Rigidbody::GetForceAcceleration() {
	XMVECTOR output = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	for (int force = mForces.size() - 1; force >= 0; force--) {
		output += *(mForces[force]);
		delete mForces[force];
		mForces.erase(mForces.begin() + force);
	}

	return output / mMass;
}