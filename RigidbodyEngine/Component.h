#pragma once
#include <string>

using namespace std;
class Component {
public:
	Component(string name);
	virtual ~Component() = default;

	string GetName();
private:
	string mName;
};