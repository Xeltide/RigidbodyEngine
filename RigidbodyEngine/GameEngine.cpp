#include "GameEngine.h"

GameEngine::GameEngine() {
	mEntityManager = new EntityManager();
	mRenderEngine = new RenderEngine(mEntityManager);
	mPhysicsEngine = new PhysicsEngine(mEntityManager);
}

GameEngine::~GameEngine() {
	delete mRenderEngine;
	delete mPhysicsEngine;
}

void GameEngine::Initialize(HWND windowHandle, UINT width, UINT height) {
	mRenderEngine->InitializeDirectX(windowHandle, width, height);

	Entity* camera = new MainCamera();
	mEntityManager->AddEntity(camera);

	Cube* cube1 = new Cube();
	mEntityManager->AddEntity(cube1);
	mRenderEngine->LoadMesh((MeshRenderer*)cube1->GetComponent("MeshRenderer"));

	Cube* cube2 = new Cube();
	Rigidbody* rb = (Rigidbody*)cube2->GetComponent("Rigidbody");
	rb->SetKinematic(true);
	Transform* trans = (Transform*)cube2->GetComponent("Transform");
	trans->Translate(0.0f, -2.0f, 0.0f);
	mEntityManager->AddEntity(cube2);
	mRenderEngine->LoadMesh((MeshRenderer*)cube2->GetComponent("MeshRenderer"));
}

void GameEngine::Update(double deltaTime) {
	// Physics step
	mPhysicsEngine->Update(deltaTime);

	// Update scripts
	vector<Entity*> scriptEntities = mEntityManager->GetComponentEntities(string("Script"));
	for (auto entity = scriptEntities.begin(); entity != scriptEntities.end(); entity++) {
		vector<Component*> scripts = (*entity)->GetComponents("Script");
		for (auto script = scripts.begin(); script != scripts.end(); script++) {
			((Script*)(*script))->Update(deltaTime);
		}
	}

	// Render entities
	mRenderEngine->Draw(deltaTime);
}