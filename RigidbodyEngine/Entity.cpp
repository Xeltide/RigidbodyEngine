#include "Entity.h"

Entity::Entity(string name) {
	mName = name;
	mComponents = new map<string, vector<Component*>>();
	//AddComponent((Component*)new Script(&this));
}

Entity::~Entity() {
	for (auto comp = (*mComponents).begin(); comp != (*mComponents).end(); comp++) {
		for (auto ind = *comp->second.begin(); ind != *comp->second.end(); ind++) {
			delete ind;
		}
	}
	delete mComponents;
}

string Entity::GetName() {
	return mName;
}

void Entity::AddComponent(Component* component) {
	(*mComponents)[component->GetName()].push_back(component);
}

Component* Entity::GetComponent(string name) {
	vector<Component*> componentList = (*mComponents)[name];
	if (componentList.size() > 0) {
		return componentList[0];
	}
	return nullptr;
}

vector<Component*> Entity::GetComponents(string name) {
	return (*mComponents)[name];
}

map<string, vector<Component*>>* Entity::GetComponentMap() {
	return mComponents;
}