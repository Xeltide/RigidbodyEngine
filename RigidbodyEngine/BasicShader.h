#pragma once
#include <DirectXMath.h>
#include "Shader.h"

using namespace DirectX;
class BasicShader : public Shader {
public:
	BasicShader(ID3D11Device1* direct3DDevice);
	virtual ~BasicShader() = default;

	void LoadShaderVertices(ID3D11Device1* direct3DDevice, MeshRenderer* mesh) override;

	void SetDevice(ID3D11DeviceContext1* direct3DDeviceContext, ID3D11Buffer** vertexBuffer) override;

private:
	typedef struct BasicShaderVertex
	{
		XMFLOAT4 Position;
		XMFLOAT4 Color;

		BasicShaderVertex() { }

		BasicShaderVertex(XMFLOAT4 position, XMFLOAT4 color)
			: Position(position), Color(color) { }
	} BasicShaderVertex;
};