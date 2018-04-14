#pragma once
#include "EntityManager.h"
#include "Rigidbody.h"
#include "BoxCollider.h"

class PhysicsEngine {
public:
	const float GRAVITY = 9.81;

	PhysicsEngine(EntityManager* entityManager);
	virtual ~PhysicsEngine();

	void Update(double deltaTime);
	bool CheckCollision(XMVECTOR colOneBBMin, XMVECTOR colOneBBMax, XMVECTOR colTwoBBMin, XMVECTOR colTwoBBMax);
	Collider::AABB MinkowskiDiff(XMVECTOR colOneBBMin, XMVECTOR colOneBBMax, XMVECTOR colTwoBBMin, XMVECTOR colTwoBBMax);
	bool MikowskiCollide(Collider::AABB colOneBB, XMVECTOR colTwoBB);

private:
	EntityManager* mEntityManager;
};