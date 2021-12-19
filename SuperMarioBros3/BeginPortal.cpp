#include "BeginPortal.h"
#include "Mario.h"
#include "Game.h"
#include "SceneManager.h"
#include "MasterMario.h"

BeginPortal::BeginPortal(Vec2 pos, Vec2 size, MapData data)
{
	state = PORTAL_STATE_IDLE;
	int direction = data.GetInt("Direction", 1);
	switch (direction)
	{
	case 1:
		this->direction = Direction::Top;
		break;
	case 2:
		this->direction = Direction::Bottom;
		break;
	case 3:
		this->direction = Direction::Left;
		break;
	case 4:
		this->direction = Direction::Right;
		break;
	}

	this->size = size;
	this->position = pos;
	this->GetBoundingBox();

	this->cameraRegionId = data.GetInt("CameraRegion", 1);

	this->destination.x = data.GetFloat("DestinationX", 0.0f);
	this->destination.y = data.GetFloat("DestinationY", 0.0f);
}

RectBox BeginPortal::GetBoundingBox() {
	this->bounding_box.left = this->position.x;
	this->bounding_box.top = this->position.y;
	this->bounding_box.right = this->bounding_box.left + size.x;
	this->bounding_box.bottom = this->bounding_box.top + size.y;
	return this->bounding_box;
}

bool BeginPortal::CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy) {
	return true;
}
void BeginPortal::Render() {
	RenderBoundingBox();
}

void BeginPortal::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CMario* mario = CMario::GetInstance();
	bool hasMario = CCollision::GetInstance()->CheckAABB(this->GetBoundingBox(), mario->GetBoundingBox());
	CGame* game = CGame::GetInstance();
	if (!hasMario) { return; }

	if (isMoving == false) {
		if (direction == Direction::Top && game->IsKeyDown(DIK_DOWN)) {
			mario->vx = 0;
			mario->vy = 0;
			mario->SetState(MARIO_STATE_WARP_VERTICAL);
			RectBox bbox = mario->GetBoundingBox();
			float marioWidth = bbox.right - bbox.left;
			mario->position.x = this->position.x - (marioWidth - size.x) / 2;
			isMoving = true;
		}
		if (direction == Direction::Bottom && game->IsKeyDown(DIK_UP)) {
			mario->vx = 0;
			mario->vy = 0;
			mario->SetState(MARIO_STATE_WARP_VERTICAL);
			RectBox bbox = mario->GetBoundingBox();
			float marioWidth = bbox.right - bbox.left;
			mario->position.x = this->position.x - (marioWidth - size.x) / 2;
			isMoving = true;
		}
	}
	else {
		if (direction == Direction::Top || direction == Direction::Bottom) {
			RectBox bbox = mario->GetBoundingBox();
			float marioWidth = bbox.right - bbox.left;
			mario->position.x = this->position.x - (marioWidth - size.x) / 2;



			if (direction == Direction::Top) {
				mario->position.y = mario->position.y + 1;

				RectBox bbox = this->GetBoundingBox();
				RectBox marioBBox = mario->GetBoundingBox();
				// need detect before mario leave portal
				if (marioBBox.top + 10 > bbox.bottom) {
					mario->SetPosition(destination);
					CGameObject* passenger = mario->GetHolder();
					if (passenger) {
						passenger->SetPosition(destination);
						SceneManager::GetInstance()->GetActiveScene()->AddObject(passenger);
					}

					SceneManager::GetInstance()->GetActiveScene()->GetCamera()->ActiveRegion(cameraRegionId);
				}
			}
			else {
				mario->position.y = mario->position.y - 1;
				RectBox bbox = this->GetBoundingBox();
				RectBox marioBBox = mario->GetBoundingBox();
				if (marioBBox.bottom + 10 > bbox.top) {
					mario->SetPosition(destination);
					CGameObject* passenger = mario->GetHolder();
					if (passenger) {
						passenger->SetPosition(destination);
						SceneManager::GetInstance()->GetActiveScene()->AddObject(passenger);
					}

					SceneManager::GetInstance()->GetActiveScene()->GetCamera()->ActiveRegion(cameraRegionId);
				}
			}


		}


	}
}

