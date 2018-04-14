#include "DemoScene.h"
#include "MeshRenderer.h"

DemoScene::DemoScene()
	: Scene() {
	Entity* test = new Entity("Test");
	MeshRenderer* testRender = new MeshRenderer();
	testRender->AddTriangle(MeshRenderer::Vertex(XMFLOAT4(-0.5f, -0.5f, -0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(0.5f, -0.5f, -0.5f, 1.0f)), MeshRenderer::Vertex(XMFLOAT4(0.5f, 0.5f, -0.5f, 1.0f)));
	test->AddComponent(testRender);
	mEntities.push_back(test);
}

DemoScene::~DemoScene() {

}