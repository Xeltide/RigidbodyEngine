#include "Scene.h"

Scene::Scene() {

}

Scene::~Scene() {
	for (auto it = mEntities.begin(); it != mEntities.end(); it++) {
		delete *it;
	}
}

vector<Entity*> Scene::GetEntities() {
	return mEntities;
}