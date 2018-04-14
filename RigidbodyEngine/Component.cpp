#include "Component.h"

Component::Component(string name) {
	mName = name;
}

string Component::GetName() {
	return mName;
}