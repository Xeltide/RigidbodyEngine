#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(EntityManager* entityManager) {
	mEntityManager = entityManager;
}

PhysicsEngine::~PhysicsEngine() {

}

/**
1) For each rigidbody, check collisions and add forces
2) Calculate new position and update

If the objects are kinematic:
- do not apply a force to that object
- remove velocity in the direction of the point of collision (maybe add a force in the opposite direction?)
**/
void PhysicsEngine::Update(double deltaTime) {

	vector<Entity*> entities = mEntityManager->GetComponentEntities("Rigidbody");
	for (auto components = entities.begin(); components != entities.end(); components++) {
		vector<Component*> rbs = (*components)->GetComponents("Rigidbody");
		vector<Rigidbody*> nonKinematic;
		for (auto rb = rbs.begin(); rb != rbs.end(); rb++) {
			Rigidbody* current = (Rigidbody*)*rb;
			if (!current->IsKinematic()) {
				// Add gravity to forces
				XMVECTOR* gravity = new XMVECTOR();
				*gravity = XMVectorSet(0.0f, -GRAVITY, 0.0f, 0.0f);
				current->AddForce(gravity);
				// Set velocity
				XMVECTOR acceleration = current->GetForceAcceleration();
				current->SetVelocity(current->GetVelocity() + (acceleration * deltaTime));
				// Apply transformation
				Transform* transform = (Transform*)(*components)->GetComponent("Transform");
				XMVECTOR velocity = current->GetVelocity() * deltaTime;
				transform->Translate(XMVectorGetX(velocity), XMVectorGetY(velocity), XMVectorGetZ(velocity));
			}
		}
	}

	for (auto entOne = entities.begin(); entOne != entities.end() - 1; entOne++) {
		for (auto entTwo = entOne + 1; entTwo != entities.end(); entTwo++) {
			// TODO: Support multiple box colliders per entity
			// Currently just takes the first box collider for comparison
			vector<Component*> colOne = (*entOne)->GetComponents("BoxCollider");
			vector<Component*> colTwo = (*entTwo)->GetComponents("BoxCollider");
			if (colOne.size() > 0 && colTwo.size() > 0) {
				BoxCollider* boxOne = (BoxCollider*)colOne[0];
				BoxCollider* boxTwo = (BoxCollider*)colTwo[0];
				// TODO: Implement rotational force
				// Points currently stay axis-aligned (redundant step)
				boxOne->CalculateAABB();
				boxTwo->CalculateAABB();
				// Collider one setup
				Collider::AABB colOneBB = boxOne->GetBoundingBox();
				Transform* colOneT = (Transform*)(*entOne)->GetComponent("Transform");
				// Collider two setup
				Collider::AABB colTwoBB = boxTwo->GetBoundingBox();
				Transform* colTwoT = (Transform*)(*entTwo)->GetComponent("Transform");
				// Check collisions
				Collider::AABB col = MinkowskiDiff(colOneBB.MinPoint, colOneBB.MaxPoint, colTwoBB.MinPoint, colTwoBB.MaxPoint);
				col.MinPoint = XMVector3Transform(col.MinPoint, colOneT->EvaluateTransform());
				col.MaxPoint = XMVector3Transform(col.MaxPoint, colOneT->EvaluateTransform());
				if (MikowskiCollide(col, colTwoT->GetOrigin())) {
					float minDist = std::abs(XMVectorGetX(colTwoT->GetOrigin()) - XMVectorGetX(col.MinPoint));
					XMVECTOR boundsPoint = XMVectorSet(-minDist, 0.0f, 0.0f, 1.0f);
					if (std::abs(XMVectorGetX(col.MaxPoint) - XMVectorGetX(colTwoT->GetOrigin())) < minDist)
					{
						minDist = std::abs(XMVectorGetX(col.MaxPoint) - XMVectorGetX(colTwoT->GetOrigin()));
						boundsPoint = XMVectorSet(minDist, 0.0f, 0.0f, 1.0f);
					}
					if (std::abs(XMVectorGetY(colTwoT->GetOrigin()) - XMVectorGetY(col.MinPoint)) < minDist) {
						minDist = std::abs(XMVectorGetY(colTwoT->GetOrigin()) - XMVectorGetY(col.MinPoint));
						boundsPoint = XMVectorSet(0.0f, minDist, 0.0f, 1.0f);
					}
					if (std::abs(XMVectorGetY(colTwoT->GetOrigin()) - XMVectorGetY(col.MaxPoint)) < minDist)
					{
						minDist = std::abs(XMVectorGetY(colTwoT->GetOrigin()) - XMVectorGetY(col.MaxPoint));
						boundsPoint = XMVectorSet(0.0f, minDist, 0.0f, 1.0f);
					}
					if (std::abs(XMVectorGetZ(colTwoT->GetOrigin()) - XMVectorGetZ(col.MaxPoint)) < minDist)
					{
						minDist = std::abs(XMVectorGetZ(colTwoT->GetOrigin()) - XMVectorGetZ(col.MaxPoint));
						boundsPoint = XMVectorSet(0.0f, 0.0f, -minDist, 1.0f);
					}
					if (std::abs(XMVectorGetZ(colTwoT->GetOrigin()) - XMVectorGetZ(col.MinPoint)) < minDist)
					{
						minDist = std::abs(XMVectorGetZ(colTwoT->GetOrigin()) - XMVectorGetZ(col.MinPoint));
						boundsPoint = XMVectorSet(0.0f, 0.0f, -minDist, 1.0f);
					}
					Rigidbody* one = (Rigidbody*)(*entOne)->GetComponent("Rigidbody");
					Rigidbody* two = (Rigidbody*)(*entTwo)->GetComponent("Rigidbody");
					if (one->IsKinematic()) {
						one->SetVelocity(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));
						two->SetVelocity(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));
						colTwoT->Translate(-XMVectorGetX(boundsPoint), -XMVectorGetY(boundsPoint), -XMVectorGetZ(boundsPoint));
					}
					else if (two->IsKinematic()) {
						one->SetVelocity(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));
						two->SetVelocity(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));
						colOneT->Translate(XMVectorGetX(boundsPoint), XMVectorGetY(boundsPoint), XMVectorGetZ(boundsPoint));
					}
					else {
						// Add velocity to colliding blocks
						XMVECTOR temp = one->GetVelocity();
						XMVECTOR* forceOne = new XMVECTOR();
						*forceOne = one->GetVelocity();
						XMVECTOR* forceTwo = new XMVECTOR();
						*forceTwo = two->GetVelocity();
						one->AddForce(forceTwo);
						two->AddForce(forceOne);
					}
				}
			}
		}
	}
}

bool PhysicsEngine::CheckCollision(XMVECTOR colOneBBMin, XMVECTOR colOneBBMax, XMVECTOR colTwoBBMin, XMVECTOR colTwoBBMax) {
	if (XMVectorGetX(colOneBBMax) > XMVectorGetX(colTwoBBMin)) {
		if (XMVectorGetX(colOneBBMin) < XMVectorGetX(colTwoBBMax)) {
			if (XMVectorGetY(colOneBBMax) > XMVectorGetY(colTwoBBMin)) {
				if (XMVectorGetY(colOneBBMin) < XMVectorGetY(colTwoBBMax)) {
					if (XMVectorGetZ(colOneBBMax) > XMVectorGetZ(colTwoBBMin)) {
						if (XMVectorGetZ(colOneBBMin) < XMVectorGetZ(colTwoBBMax)) {
							return true;
						}
					}
				}
			}
		}
	}


	return false;
}

Collider::AABB PhysicsEngine::MinkowskiDiff(XMVECTOR colOneBBMin, XMVECTOR colOneBBMax, XMVECTOR colTwoBBMin, XMVECTOR colTwoBBMax) {
	Collider::AABB output;
	output.MinPoint = colOneBBMin + colTwoBBMin;
	output.MaxPoint = colTwoBBMax + colOneBBMax;
	return output;
}

bool PhysicsEngine::MikowskiCollide(Collider::AABB colOneBB, XMVECTOR colTwoBB) {
	if (XMVectorGetX(colOneBB.MaxPoint) > XMVectorGetX(colTwoBB)) {
		if (XMVectorGetX(colOneBB.MinPoint) < XMVectorGetX(colTwoBB)) {
			if (XMVectorGetY(colOneBB.MaxPoint) > XMVectorGetY(colTwoBB)) {
				if (XMVectorGetY(colOneBB.MinPoint) < XMVectorGetY(colTwoBB)) {
					if (XMVectorGetZ(colOneBB.MaxPoint) > XMVectorGetZ(colTwoBB)) {
						if (XMVectorGetZ(colOneBB.MinPoint) < XMVectorGetZ(colTwoBB)) {
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}