#pragma once
#include "Utils.h"
#include "Collision.h"
#include "RectBox.h"
using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject
{

protected:

	DWORD id;
	float x;
	float y;

	float vx;
	float vy;
	Vec2 position;
	float gravity;

	int nx;

	int state;
	int ani;
	bool isDeleted;
	bool is_show = true;
	RectBox bounding_box;
public:
	int type;
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void SetVelocityX(float _vx) { this->vx = _vx; }
	void SetVelocityY(float _vy) { this->vy = _vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	float GetPositionX() { return this->x; }
	float GetPositionY() { return this->y; }

	Vec2 GetPosition() { return this->position; }
	void SetPosition(Vec2 pos) { this->position = pos; }

	void SetPositionX(float _x) { this->x = _x; }
	void SetPositionY(float _y) { this->y = _y; }

	float GetGravity() { return this->gravity; }
	void SetGravity(float _gravity) { this->gravity = _gravity; }

	int GetNx() { return this->nx; }
	void SetNx(int _nx) { this->nx = _nx; }

	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }
	virtual void Delete() { isDeleted = true; }
	bool IsDeleted() { return isDeleted; }


	void RenderBoundingBox();

	CGameObject();
	CGameObject(float x, float y) :CGameObject() {
		this->x = x; this->y = y;
	}

	virtual RectBox GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return 1; }

	~CGameObject();
	virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);
	static bool IsDeleted(const LPGAMEOBJECT& o) { return o->isDeleted; }

	DWORD GetID() {
		return id;
	}
};
