#pragma once
#include <Windows.h>
#include "Transform.h"

class EntityManager;
class Entity;

class Script : public Component {
public:
	Script(Entity* self);
	virtual ~Script() = default;

	virtual void Update(double deltaTime) = 0;

protected:
	Entity* mSelf;
	EntityManager* mEntities;
};