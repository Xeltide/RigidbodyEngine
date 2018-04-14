#include "CameraScript.h"
#include "EntityManager.h"
#include "Camera.h"

CameraScript::CameraScript(Entity* self)
	: Script(self) {

}

void CameraScript::Update(double deltaTime) {
	// 'A' key press
	if (GetAsyncKeyState(0x41)) {
		Camera* transform = (Camera*)(mSelf->GetComponent(string("Camera")));
		XMVECTOR translation = transform->Right() * -deltaTime;
		transform->Translate(translation);
	}
	// 'D' key press
	if (GetAsyncKeyState(0x44)) {
		Camera* transform = (Camera*)(mSelf->GetComponent(string("Camera")));
		XMVECTOR translation = transform->Right() * deltaTime;
		transform->Translate(translation);
	}
	// 'Q' key press
	if (GetAsyncKeyState(0x51)) {

	}
	// 'S' key press
	if (GetAsyncKeyState(0x53)) {
		Camera* transform = (Camera*)(mSelf->GetComponent(string("Camera")));
		XMVECTOR translation = transform->Normal() * deltaTime;
		transform->Translate(translation);
	}
	// 'W' key press
	if (GetAsyncKeyState(0x57)) {
		Camera* transform = (Camera*)(mSelf->GetComponent(string("Camera")));
		XMVECTOR translation = transform->Normal() * -deltaTime;
		transform->Translate(translation);
	}
}