#pragma once
#include <D3D11.h>
#include <D3Dcompiler.h>
#include <string>
#include <d3dx11Effect.h>
#include "MeshRenderer.h"

#define ReleaseObject(object) if((object) != NULL) { object->Release(); object = NULL; }

using namespace std;
class Shader {
public:
	Shader(string name, string filePath);
	virtual ~Shader() = default;

	void Load(ID3D11Device1* mDirect3DDevice);
	ID3DX11EffectPass* GetPass();
	ID3DX11Effect* GetEffect();
	void SetTechPass(const char* techName, const char* passName);
	void SetInputLayout(ID3D11Device1* direct3DDevice, D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[], UINT descNumber);

	virtual void LoadShaderVertices(ID3D11Device1* direct3DDevice, MeshRenderer* mesh) = 0;
	virtual void SetDevice(ID3D11DeviceContext1* direct3DDeviceContext, ID3D11Buffer** vertexBuffer) = 0;


protected:
	string mName;
	string mFilePath;

	ID3D11InputLayout* mInputLayout;
	ID3DX11Effect* mEffect;
	ID3DX11EffectTechnique* mTechnique;
	ID3DX11EffectPass* mPass;
};