#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
	: Component(string("MeshRenderer")) {

}

void MeshRenderer::AddTriangle(Vertex p1, Vertex p2, Vertex p3) {
	mVertices.push_back(p1);
	mVertices.push_back(p2);
	mVertices.push_back(p3);
}

void MeshRenderer::RemoveTriangle(unsigned int index) {
	if (index < TriangleCount()) {
		mVertices.erase(mVertices.begin() + (index * 3), mVertices.begin() + (index * 3) + 3);
	}
}

unsigned int MeshRenderer::TriangleCount() {
	return mVertices.size() / 3;
}

vector<MeshRenderer::Vertex> MeshRenderer::GetVertices() {
	return mVertices;
}

ID3D11Buffer** MeshRenderer::GetVertexBuffer() {
	return &mVertexBuffer;
}

UINT MeshRenderer::GetBufferSize() {
	return mVertices.size();
}

void MeshRenderer::SetVertexBuffer(ID3D11Buffer* vertexBuffer) {
	mVertexBuffer = vertexBuffer;
}

string MeshRenderer::GetShaderName() {
	return mShaderName;
}

void MeshRenderer::SetShaderName(string name) {
	mShaderName = name;
}