#include "ShaderManager.h"

ShaderManager::ShaderManager(ID3D11Device1* direct3DDevice) {
	BasicShader* basic = new BasicShader(direct3DDevice);
	mShaders.insert(pair<string, Shader*>(string("Basic"), basic));
}

Shader* ShaderManager::GetShader(string name) {
	return mShaders[name];
}