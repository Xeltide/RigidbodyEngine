#include "BasicShader.h"

BasicShader::BasicShader(ID3D11Device1* direct3DDevice)
	: Shader(string("Basic"), string("BasicEffect.fx")) {
	Load(direct3DDevice);
	SetTechPass("main11", "p0");

	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	SetInputLayout(direct3DDevice, desc, 2);
}

void BasicShader::LoadShaderVertices(ID3D11Device1* direct3DDevice, MeshRenderer* mesh) {
	vector<MeshRenderer::Vertex> vertices = mesh->GetVertices();
	// TODO: This is a memory leak
	// Delete it through pointer in SUBRESOURCE_DATA
	BasicShaderVertex* shaderV = new BasicShaderVertex[vertices.size()];
	UINT i = 0;
	for (auto vert = vertices.begin(); vert != vertices.end(); vert++) {
		BasicShaderVertex vertex(vert->Position, XMFLOAT4(1.0, 1.0, 1.0, 1.0));
		shaderV[i] = vertex;
		i++;
	}

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.ByteWidth = sizeof(BasicShaderVertex) * vertices.size();
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//A subsource is a mip-map level
	//The vertex buffer above is Immutable thus cannot be modified
	//A subresource initialized with the vertex buffer data is instead used 
	D3D11_SUBRESOURCE_DATA vertexSubResourceData;
	ZeroMemory(&vertexSubResourceData, sizeof(vertexSubResourceData));
	vertexSubResourceData.pSysMem = shaderV;

	//Create buffer will hold the mutable vertices used by the GPU
	ID3D11Buffer* vertexBuffer;
	if (FAILED(direct3DDevice->CreateBuffer(&vertexBufferDesc, &vertexSubResourceData, &vertexBuffer)))
	{
		//throw GameException("ID3D11Device::CreateBuffer() failed.");
	}
	else {
		mesh->SetVertexBuffer(vertexBuffer);
		mesh->SetShaderName(mName);
	}
}

void BasicShader::SetDevice(ID3D11DeviceContext1* direct3DDeviceContext, ID3D11Buffer** vertexBuffer) {
	direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	direct3DDeviceContext->IASetInputLayout(mInputLayout);

	UINT stride = sizeof(BasicShaderVertex);
	UINT offset = 0;
	direct3DDeviceContext->IASetVertexBuffers(0, 1, vertexBuffer, &stride, &offset);
}