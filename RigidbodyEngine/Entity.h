#pragma once
#include <string>
#include <map>
#include <vector>
#include "Component.h"
#include "Script.h"

using namespace std;
class Entity {
public:
	Entity(string name);
	virtual ~Entity();

	string GetName();
	void AddComponent(Component* component);
	Component* GetComponent(string name);
	vector<Component*> GetComponents(string name);
	map<string, vector<Component*>>* GetComponentMap();

private:
	string mName;
	map<string, vector<Component*>>* mComponents;
};