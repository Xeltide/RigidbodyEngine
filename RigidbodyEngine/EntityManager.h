#pragma once
#include <map>
#include <vector>
#include <string>
#include "Scene.h"

using namespace std;
class EntityManager {
public:
	EntityManager();
	virtual ~EntityManager();

	void AddEntity(Entity* entity);
	Entity* GetEntityByName(string name);
	vector<Entity*> GetEntitiesByName(string name);
	vector<Entity*> GetComponentEntities(string componentName);

	void LoadScene(Scene* scene);
	void ClearEntities();
private:
	map<string, vector<Entity*>>* mEntities;
	map<string, vector<Entity*>>* mComponentEntities;
};