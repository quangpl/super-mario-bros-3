#pragma once
#include "Utils.h"
#include "Game.h"
#include "GameObject.h"
#include "Direction.h"
#include "RectBox.h"
#include "debug.h"
#include "CameraRegion.h"

class Camera
{
	Vec2 size;
	CGameObject* tracking_object = NULL;
	unordered_map<int, CameraRegion*> regions;
	int active_region_id = 0;
	RectBox active_bound;
	int reset = 0;
public:
	Vec2 position;
	Camera();
	Camera(Vec2 size);

	CGameObject* GetTrackingObject() { return this->tracking_object; }
	void SetTrackingObject(CGameObject* _tracking_object) {  this->tracking_object = _tracking_object; }


	Vec2 GetPosition() { return this->position; }
	virtual Vec2 GetCamSize();
	virtual RectBox GetBoundingBox();
	virtual void Update();
	virtual void ActiveRegion(int id);
	virtual CameraRegion* GetActiveRegion();
	virtual void LoadFromTMX(TiXmlElement* data);

	bool IsInCamera(CGameObject* obj);

	~Camera();
};

