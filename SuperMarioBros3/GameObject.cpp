#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
	state = -1;
	isDeleted = false;
	id = starting_id++;
}
RectBox CGameObject::GetBoundingBox() {
	return RectBox(0, 0, 0, 0);
}
void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get("tex-test");

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)bounding_box.right - (int)bounding_box.left;
	rect.bottom = (int)bounding_box.bottom - (int)bounding_box.top;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw((bounding_box.right + bounding_box.left)/ 2 - cx,(bounding_box.top + bounding_box.bottom)/ 2 - cy, bbox, rect.left, rect.top, rect.right, rect.bottom, 0.45f);
}

CGameObject::~CGameObject()
{

}

bool CGameObject::CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy)
{
	return false;
}