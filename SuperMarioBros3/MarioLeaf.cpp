#include "MarioLeaf.h"

MarioLeaf::MarioLeaf(Vec2 pos) {
	this->position = pos;
	this->startingPos = pos;
	nx = -1;
	gravity = 0;
}

MarioLeaf::~MarioLeaf()
{

}


bool MarioLeaf::CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy) {
	return true;
}
void MarioLeaf::Render()
{
	Vec2 cam = SceneManager::GetInstance()->GetActiveScene()->GetCamera()->GetPosition();
	CAnimations::GetInstance()->Get("ani-super-leaf-red")->GetTransform()->Scale.x = -nx;
	CAnimations::GetInstance()->Get("ani-super-leaf-red")->GetTransform()->Position = GetPosition() - cam + Vec2{ LEAF_SIZE ,LEAF_SIZE } / 2;
	CAnimations::GetInstance()->Get("ani-super-leaf-red")->Render(position.x, position.y);
	RenderBoundingBox();
}

void MarioLeaf::OnNoCollision(DWORD dt)
{
}
void MarioLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	switch (fallingStep)
	{
	case 0:
		if (position.y + LEAF_SIZE + 194.0f <= startingPos.y) {
			position.y = startingPos.y - LEAF_SIZE - 144.0f;
			vy = 0;
			fallingStep = 1;
		}
		else {
			if (this->isDeleted && position.y + 10.0f <= startingPos.y) {
				this->isDeleted = false;
			}
			vy -= LEAF_GROWUP_SPEED * dt;
		}
		break;
	case 1:
		this->gravity = LEAF_GRAVITY;
		this->zIndex = 1501;

		if (abs(position.x - startingPos.x) >= LEAF_REVEAL_DISTANCE) {
			nx = position.x < startingPos.x ? 1 : -1;
		}

		vx = LEAF_REVEAL_FORCE * dt * nx;

		break;
	default:
		break;
	}

	vy = min(vy + gravity * dt, LEAF_FALLING_VEL);
	position.x += vx * dt;
	position.y += vy * dt;
}

RectBox MarioLeaf::GetBoundingBox() {
	this->bounding_box.left = position.x;
	this->bounding_box.top = position.y;
	this->bounding_box.right = this->bounding_box.left + BRICK_BBOX_WIDTH;
	this->bounding_box.bottom = this->bounding_box.top + BRICK_BBOX_HEIGHT;
	return this->bounding_box;
}
