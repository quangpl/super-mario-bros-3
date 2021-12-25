#include <d3dx9.h>
#include <algorithm>

#include "SceneManager.h"
#include "debug.h"
#include "PlayScene.h"
#include "Textures.h"
#include "Game.h"
#include "Camera.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	position = Vec2{ 0,0 };
	vx = vy = 0;
	nx = 1;
	state = -1;
	isDeleted = false;
}

void CGameObject::OnGoingToCamera() {

}

void CGameObject::OnLeavingCamera() {

}

Vec2 CGameObject::GetSize() {
	RectBox bbox = this->GetBoundingBox();
	float width = bbox.right - bbox.left;
	float height = bbox.bottom - bbox.top;
	return Vec2{ width, height };
}


RectBox CGameObject::GetBoundingBox() {
	return RectBox(0, 0, 0, 0);
}

void CGameObject::RenderBoundingBox()
{
	GetBoundingBox();
	D3DXVECTOR3 p(position.x, position.y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get("tex-test");

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)bounding_box.right - (int)bounding_box.left;
	rect.bottom = (int)bounding_box.bottom - (int)bounding_box.top;
	Camera* camera = SceneManager::GetInstance()->GetActiveScene()->GetCamera();
	float cx, cy;
	cx = camera->position.x;
	cy = camera->position.y;
	D3DXVECTOR3 pivot = { 0, 0, 0 };
	Transformation trans;
	CGame::GetInstance()->Draw((bounding_box.right + bounding_box.left) / 2 - cx, (bounding_box.top + bounding_box.bottom) / 2 - cy, pivot, bbox, rect, trans, 0.45f);
}

CGameObject::~CGameObject()
{

}

bool CGameObject::CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy)
{
	return false;
}