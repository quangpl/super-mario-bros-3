#pragma once
#include "Utils.h"
#include "RectBox.h"
#include "Direction.h"

enum class CameraMode {
	TRACKING,
	AUTOSCROLL
};

class CameraRegion
{
protected:
	int id;

	RectBox boundary{ -9999, -9999, 99999, 99999 };

	RectBox inside{ -9999, -9999, 9999, 9999 };

	CameraMode mode = CameraMode::TRACKING;

	Vec2 velocity = VECTOR_0;

public:
	CameraRegion(TiXmlElement* config);

	void SetID(int value);
	int GetID();

	void SetBoundary(RectBox value);
	RectBox GetBoundary();

	void SetCameraMode(CameraMode value);
	CameraMode GetCameraMode();

	void SetInsideBoundary(RectBox value);
	RectBox GetInsideBoundary();

	// van toc di chuyen cam
	void SetVelocity(Vec2 value);
	Vec2 GetVelocity();

};

