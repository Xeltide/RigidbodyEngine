#include "MainCamera.h"
#include "Camera.h"

MainCamera::MainCamera()
	: Entity(string("MainCamera")) {
	AddComponent(new Transform());
	AddComponent(new Camera());
	AddComponent(new CameraScript(this));
}

MainCamera::~MainCamera() {

}