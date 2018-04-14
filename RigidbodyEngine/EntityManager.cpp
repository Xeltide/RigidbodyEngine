#include "EntityManager.h"

EntityManager::EntityManager() {
	mEntities = new map<string, vector<Entity*>>();
	mComponentEntities = new map<string, vector<Entity*>>();
}

EntityManager::~EntityManager() {
	delete mEntities;
	delete mComponentEntities;
}

void EntityManager::AddEntity(Entity* entity) {
	// Add entry to entity list with unique name
	(*mEntities)[entity->GetName()].push_back(entity);

	// Add entity to component lookup
	map<string, vector<Component*>>* componentMap = entity->GetComponentMap();
	for (auto it = componentMap->begin(); it != componentMap->end(); it++) {
		(*mComponentEntities)[it->first].push_back(entity);
	}
}

Entity* EntityManager::GetEntityByName(string name) {
	vector<Entity*> namedEntities = (*mEntities)[name];

	if (namedEntities.size() > 0) {
		return namedEntities[0];
	}

	return nullptr;
}

vector<Entity*> EntityManager::GetEntitiesByName(string name) {
	return (*mEntities)[name];
}

vector<Entity*> EntityManager::GetComponentEntities(string name) {
	return (*mComponentEntities)[name];
}

void EntityManager::LoadScene(Scene* scene) {
	vector<Entity*> entities = scene->GetEntities();
	for (auto ent = entities.begin(); ent != entities.end(); ent++) {
		AddEntity(*ent);
	}
}

void EntityManager::ClearEntities() {
	mEntities->clear();
	mComponentEntities->clear();
}