#include "Fireball.h"
#include "Mario.h"

Fireball::Fireball() :CGameObject()
{
	zIndex = 15;
	gravity = 0;
}

void Fireball::Shoot(RectBox box, int nx) {
	this->nx = nx;
	CMario* mario = CMario::GetInstance();
	Vec2 marioPosition = mario->GetPosition();
	this->position.x = box.left + FIREBALL_SIZE / 2;
	this->position.y = box.top + POSITION_ADJUSTMENT;

	Vec2 directionVector = marioPosition - position;

	float ray = 0;
	Vec2 distance = this->GetUnitVector(marioPosition - position);

	if (abs(distance.x) > CELL_SIZE * 6 || abs(distance.y) < CELL_SIZE * 2)
		ray = (distance.x > 0 ? 25 : 155) * (distance.y < 0 ? -1 : 1);
	else
		ray = (distance.x > 0 ? 45 : 135) * (distance.y < 0 ? -1 : 1);

	ray = ray * PI_CONSTANT / 180.0f; // chuyen tu do qua radian
	directionVector = GetUnitVector(Vec2(cos(ray), sin(ray))); // tinh vector don vi

	Vec2 v = directionVector * FIREBALL_SPEED;
	vx = v.x;
	vy = v.y;

}
//Tim vector don vi : https://tintuctuyensinh.vn/don-vi-vector/?fbclid=IwAR2MtoxYo6f3qihItiKc8QMxYkh5rFKp4UvzANZlgpbSoPLZAmRpoiVKzI8
Vec2 Fireball::GetUnitVector(Vec2 vec) {
	float m = sqrt(vec.x * vec.x + vec.y * vec.y);
	return vec / m;
}
bool Fireball::CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy) {
	if (dynamic_cast<CMario*>(gameObjToCollide)) {
		return false;
	}
	return true;
}

RectBox Fireball::GetBoundingBox() {
	this->bounding_box.left = position.x - FIREBALL_SIZE / 2;
	this->bounding_box.top = position.y - FIREBALL_SIZE / 2;
	this->bounding_box.right = this->bounding_box.left + FIREBALL_SIZE;
	this->bounding_box.bottom = this->bounding_box.top + FIREBALL_SIZE;
	return this->bounding_box;
}

void Fireball::OnNoCollision(DWORD dt)
{
	position.x += vx * dt;
	position.y += vy * dt;
};

void Fireball::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void Fireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
int Fireball::IsCollidable() {
	return 0;
}

void Fireball::Render()
{
	CAnimations::GetInstance()->Get("ani-fire-ball")->Render(position.x, position.y);
	RenderBoundingBox();
}

void Fireball::SetState(int state)
{
	CGameObject::SetState(state);
}
