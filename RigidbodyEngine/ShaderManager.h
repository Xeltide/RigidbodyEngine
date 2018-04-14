#pragma once
#include <map>
#include <string>
#include "BasicShader.h"

using namespace std;
class ShaderManager {
public:
	ShaderManager(ID3D11Device1* direct3DDevice);
	virtual ~ShaderManager() = default;

	Shader* GetShader(string name);

private:
	map<string, Shader*> mShaders;
};