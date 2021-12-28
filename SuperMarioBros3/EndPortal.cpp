#include "EndPortal.h"
#include "Mario.h"
#include "Game.h"
#include "SceneManager.h"
#include "MasterMario.h"

EndPortal::EndPortal(Vec2 pos, Vec2 size, MapData data)
{
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
}


RectBox EndPortal::GetBoundingBox() {
	this->bounding_box.left = this->position.x;
	this->bounding_box.top = this->position.y;
	this->bounding_box.right = this->bounding_box.left + size.x;
	this->bounding_box.bottom = this->bounding_box.top + size.y;
	return this->bounding_box;
}

bool EndPortal::CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy) {
	return true;
}
void EndPortal::Render() {
	RenderBoundingBox();
}

void EndPortal::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CMario* mario = CMario::GetInstance();
	bool hasMario = CCollision::GetInstance()->CheckAABB(this->GetBoundingBox(), mario->GetBoundingBox());

	if (!hasMario) return;
	
	if (direction == Direction::Top || direction == Direction::Bottom) {
		CGame::GetInstance()->DisableKeyboard();
		mario->vx = 0;
		mario->vy = 0;
		RectBox bbox = mario->GetBoundingBox();
		float marioWidth = bbox.right - bbox.left;
		mario->position.x = this->bounding_box.left + (marioWidth - size.x) / 2;
		mario->GetPlayerState()->SetState(MARIO_STATE_WARP_VERTICAL);
		if (direction == Direction::Top) {
			mario->position.y = mario->position.y + 1.1;
		}
		else {
			mario->position.y = mario->position.y - 1.1;
		}
	}
	
	hasMario = CCollision::GetInstance()->CheckAABB(this->GetBoundingBox(), mario->GetBoundingBox());
	if (!hasMario){
		CGame::GetInstance()->EnableKeyboard();
		mario->SetState(MARIO_STATE_IDLE);
	}
}

