#pragma once
#include "EntityManager.h"
#include "RenderEngine.h"
#include "PhysicsEngine.h"
#include "MainCamera.h"
#include "Cube.h"

class GameEngine {
public:
	GameEngine();
	virtual ~GameEngine();

	void Initialize(HWND windowHandle, UINT width, UINT height);
	void Update(double deltaTime);

private:
	EntityManager* mEntityManager;
	RenderEngine* mRenderEngine;
	PhysicsEngine* mPhysicsEngine;
};