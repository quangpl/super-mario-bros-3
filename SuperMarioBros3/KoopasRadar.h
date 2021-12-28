#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Koopas.h"

#define KOOPAS_RADAR_SIZE 16
#define KOOPAS_RADAR_OWNER_DISTANCE 3

class CKoopasRadar : public CGameObject
{
	CKoopas* owner;
protected:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual RectBox GetBoundingBox();
public:
	CKoopasRadar(CKoopas* owner);
	virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);
};