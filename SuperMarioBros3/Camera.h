#pragma once
#include "Utils.h"
#include "Game.h"
#include "GameObject.h"
#include "Direction.h"
#include <memory>
#include "RectBox.h"
#include "debug.h"
#include "CameraRegion.h"

class Camera
{
	Vec2 size;

	unordered_map<int, CameraRegion*> regions;
	int active_region_id = 0;
	RectBox active_bound;
	int reset = 0;
public:
	Vec2 position;
	Camera();
	Camera(Vec2 size);


	virtual Vec2 GetCamSize();

	virtual RectBox GetBoundingBox();

	virtual void Update();

	virtual void ActiveRegion(int id);
	virtual CameraRegion* GetActiveRegion();

	virtual void LoadFromTMX(TiXmlElement* data);

	~Camera();
};

