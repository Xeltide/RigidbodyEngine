#pragma once
#include "Script.h"

class CameraScript : public Script {
public:
	CameraScript(Entity* self);
	virtual ~CameraScript() = default;

	void Update(double deltaTime) override;
};