#include "Cube.h"

Cube::Cube()
	: Entity(string("Cube")) {
	// Set transform
	Transform* t = new Transform();
	t->Translate(0.0f, 0.0f, -5.0f);

	// Set renderer
	MeshRenderer* render = new MeshRenderer();
	// Back face
	render->AddTriangle(MeshRenderer::Vertex(XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f)));
	render->AddTriangle(MeshRenderer::Vertex(XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f)));

	// Front face
	render->AddTriangle(MeshRenderer::Vertex(XMFLOAT4(-0.5f, -0.5f, -0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(0.5f, -0.5f, -0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(0.5f, 0.5f, -0.5f, 1.0f)));
	render->AddTriangle(MeshRenderer::Vertex(XMFLOAT4(-0.5f, 0.5f, -0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(-0.5f, -0.5f, -0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(0.5f, 0.5f, -0.5f, 1.0f)));

	// Right face
	render->AddTriangle(MeshRenderer::Vertex(XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(0.5f, 0.5f, -0.5f, 1.0f)));
	render->AddTriangle(MeshRenderer::Vertex(XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(0.5f, -0.5f, -0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(0.5f, 0.5f, -0.5f, 1.0f)));

	// Set rigidbody
	Rigidbody* r = new Rigidbody();
	XMVECTOR* iForce = new XMVECTOR();
	*iForce = XMVectorSet(10000.0f, 0.0f, 0.0f, 1.0f);
	//r->AddForce(iForce);

	BoxCollider* collider = new BoxCollider();
	collider->GeneratePoints(XMVECTOR());

	AddComponent(t);
	AddComponent(render);
	AddComponent(r);
	AddComponent(collider);
}

Cube::~Cube() {

}