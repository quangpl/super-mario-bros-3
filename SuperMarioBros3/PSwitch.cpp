#include "PSwitch.h"
#include "Mario.h"
#include "Coin.h"


PSwitch::PSwitch(Vec2 pos) {
	SetState(PSWITCH_STATE_NORMAL);
	this->position = pos;
	// Should consider "source" object
	this->position.y = position.y - BRICK_BBOX_HEIGHT;
}

PSwitch::~PSwitch()
{

}


void PSwitch::Render()
{
	if (state == PSWITCH_STATE_NORMAL) {
		ani = "ani-switch-block";
	}
	else {
		ani = "ani-switch-block-pressed";
	}
	CAnimations::GetInstance()->Get(ani)->Render(position.x + PSWITCH_SIZE / 2, position.y + PSWITCH_SIZE / 2);
	RenderBoundingBox();
}

void PSwitch::OnNoCollision(DWORD dt)
{
	position.x += vx * dt;
	position.y += vy * dt;
}

int PSwitch::IsCollidable()
{
	return true;
}

void PSwitch::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->ny > 0 && dynamic_cast<CMario*>(e->obj))
	{
		SetState(PSWITCH_STATE_PRESSED);
	}
}
void PSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt, objects);
	CCollision::GetInstance()->Process(this, dt, objects);
}

void PSwitch::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == PSWITCH_STATE_PRESSED) {
		this->position.y = this->position.y + 30;
		vy = 1;
		vector<CGameObject*> gameObjects = SceneManager::GetInstance()->GetActiveScene()->GetObjects();
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			if (dynamic_cast<CCoin*>(gameObjects[i])) {
				CCoin* coin = dynamic_cast<CCoin*>(gameObjects[i]);
				coin->Switch();
			}
		}
	}
}
RectBox PSwitch::GetBoundingBox() {
	int height = state == PSWITCH_STATE_NORMAL ? PSWITCH_SIZE : PSWITCH_SIZE - 30;
	this->bounding_box.left = position.x;
	// move down a little bit for border of PSwitch
	this->bounding_box.top = position.y;
	this->bounding_box.right = this->bounding_box.left + PSWITCH_SIZE;
	this->bounding_box.bottom = this->bounding_box.top + height;
	return this->bounding_box;
}
