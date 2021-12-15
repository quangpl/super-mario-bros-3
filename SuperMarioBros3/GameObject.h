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
	float gravity;
	int nx;
	int state;
	bool isDeleted;
public:
	int zIndex = 1; // It will stand for render priority
	RectBox bounding_box;
	string ani;
	float vx;
	float vy;
	Vec2 position;
	bool is_in_camera = false;
	int type;
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void SetVelocityX(float _vx) { this->vx = _vx; }
	void SetVelocityY(float _vy) { this->vy = _vy; }

	Vec2 GetSpeed() {
		return Vec2{ this->vx, this->vy };
	}
	Vec2 GetPosition() { return this->position; }
	void SetPosition(Vec2 pos) { this->position = pos; }

	float GetGravity() { return this->gravity; }
	void SetGravity(float _gravity) { this->gravity = _gravity; }

	int GetNx() { return this->nx; }
	void SetNx(int _nx) { this->nx = _nx; }

	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }
	virtual void Delete() { isDeleted = true; }
	bool IsDeleted() { return isDeleted; }
	void SetDeleted(bool del) {
		isDeleted = del;
	}

	void RenderBoundingBox();

	CGameObject();
	virtual RectBox GetBoundingBox();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	virtual void OnGoingToCamera();
	virtual void OnLeavingCamera();

	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

	virtual void OnBlockingOnX(int jetX) {};

	virtual void OnBlockingOnY(int jetY) {};

	~CGameObject();
	virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);
	static bool IsDeleted(const LPGAMEOBJECT& o) { return o->isDeleted; }

	DWORD GetID() {
		return id;
	}
};
