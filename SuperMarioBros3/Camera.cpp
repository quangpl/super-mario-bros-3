#include "Camera.h"


Camera::Camera()
{
	this->position = VECTOR_0;
}

Camera::Camera(Vec2 size)
{
	//this->position = Vec2(100, 850);
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
	RectBox targetBound = tracking_object->GetBoundingBox();
	float avgY = (targetBound.top + targetBound.bottom - size.y) / 2;

	position.x = (targetBound.left - size.x / 2);
	position.y = min(avgY + size.y / 4, max(position.y, avgY - size.y / 4));

	Vec2 camSize = GetCamSize();
	RectBox camBound = GetBoundingBox();
	RectBox camLimit = active_bound;

	if (reset == 1) {
		RectBox originalBound = regions[active_region_id]->GetBoundary();
		if (camBound.left >= originalBound.left && camBound.right <= originalBound.right
			&& camBound.top >= originalBound.top && camBound.bottom <= originalBound.bottom)
		{
			camLimit = active_bound = originalBound;
			reset = 2;
		}
	}

	if (camBound.left < camLimit.left) position.x = camLimit.left;
	if (camBound.top < camLimit.top) position.y = camLimit.top;
	if (camBound.right > camLimit.right) position.x = camLimit.right - camSize.x;
	if (camBound.bottom > camLimit.bottom) position.y = camLimit.bottom - camSize.y;
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

void Camera::SetLimitEdge(Direction edge, float value)
{
	reset = 0;
	switch (edge)
	{
	case Direction::Left:
		active_bound.left = value;
		break;
	case Direction::Top:
		active_bound.top = value;
		break;
	case Direction::Right:
		active_bound.right = value;
		break;
	case Direction::Bottom:
		active_bound.bottom = value;
		break;
	}
}

void Camera::ResetLimitEdge()
{
	if (!reset) reset = 1;
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
