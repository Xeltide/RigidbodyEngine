#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include "Component.h"

using namespace std;
using namespace DirectX;
class MeshRenderer : public Component {
public:
	typedef struct Vertex {
		XMFLOAT4 Position;

		Vertex(XMFLOAT4 Position) : Position(Position) {};
	} Vertex;

	MeshRenderer();
	virtual ~MeshRenderer() = default;

	void AddTriangle(Vertex p1, Vertex p2, Vertex p3);
	void RemoveTriangle(unsigned int index);
	unsigned int TriangleCount();

	vector<Vertex> GetVertices();
	ID3D11Buffer** GetVertexBuffer();
	UINT GetBufferSize();
	void SetVertexBuffer(ID3D11Buffer* vertexBuffer);
	string GetShaderName();
	void SetShaderName(string name);

private:
	string mShaderName;
	vector<Vertex> mVertices;
	ID3D11Buffer* mVertexBuffer;
};