#include "Camera.h"


Camera::Camera()
{
	this->position = VECTOR_0;
}

Camera::Camera(Vec2 size)
{
	this->position = Vec2(100, 850);
	this->size = size;
}

Vec2 Camera::GetCamSize()
{
	return size;
}

RectBox Camera::GetBoundingBox()
{
	return RectBox(position.x, position.y, position.x + size.x, position.y + size.y);
}


void Camera::Update()
{
	RectBox trackingObjectBox = tracking_object->GetBoundingBox();
	RectBox camLimitation = active_bound;
	DebugOut(L"position %f %f \n", position.x, position.y);
	/*if (abs(trackingObjectBox.left - camLimitation.left) <= size.x / 2) {
		position.x = camLimitation.left;
	}
	else if (abs(trackingObjectBox.right - camLimitation.right) <= size.x / 2) {
		position.x = camLimitation.right;
	}
	else {
		position.x = trackingObjectBox.left - size.x / 2;
	}*/
}
void Camera::ActiveRegion(int id)
{
	if (regions.find(id) == regions.end() || regions.at(id) == nullptr) {
		return;
	}
	active_region_id = id;
	active_bound = regions.at(id)->GetBoundary();
}

CameraRegion* Camera::GetActiveRegion()
{
	return regions[active_region_id];
}


void Camera::LoadFromTMX(TiXmlElement* config)
{
	int startId = 0;

	config->QueryIntAttribute("start", &startId);

	for (TiXmlElement* node = config->FirstChildElement("Region"); node != nullptr; node = node->NextSiblingElement("Region"))
	{
		CameraRegion* region = new CameraRegion(node);
		regions[region->GetID()] = region;
	}

	ActiveRegion(startId);
}
bool Camera::IsInCamera(CGameObject* obj) {
	RectBox objectBoundingBox = obj->GetBoundingBox();
	return !(objectBoundingBox.right <= active_bound.left || objectBoundingBox.left >= active_bound.right || objectBoundingBox.top >= active_bound.bottom || objectBoundingBox.bottom <= active_bound.top);
}

Camera::~Camera()
{
}
