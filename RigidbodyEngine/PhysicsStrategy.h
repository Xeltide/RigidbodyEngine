#pragma once


class PhysicsStrategy {
public:

	enum class Broad {
		AABB,
		None
	};

	enum class Narrow {
		None
	};

	PhysicsStrategy();
	PhysicsStrategy(Broad broadPhase, Narrow narrowPhase);
	virtual ~PhysicsStrategy();

	void CheckCollision();

private:
	Broad mBroadPhase;
	Narrow mNarrowPhase;
};