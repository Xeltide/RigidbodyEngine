#include "Script.h"
#include "EntityManager.h"

Script::Script(Entity* self)
	: Component(string("Script")){
	mSelf = self;
}

//void Script::Update(double deltaTime) {
//	// Placeholder update function to be called on empty entities
//}