#pragma once
#include <vector>
#include "Entity.h"

using namespace std;
class Scene {
public:
	Scene();
	virtual ~Scene();

	vector<Entity*> GetEntities();

protected:
	vector<Entity*> mEntities;
};