#pragma once
#include "MapData.h"
#include "GameObject.h"
#include "Constants.h"
#include "Koopas.h"

#define COMMAND_KOOPAS_TURNBACK "koopas_turnback"

class CCommandPoint :public CGameObject
{
	Vec2 size;
	string command;
public:
	CCommandPoint();
	static CCommandPoint* Create(Vec2 pos, MapData& data);
	virtual void Render();
	virtual RectBox GetBoundingBox();
	
	string GetCommand() { return this->command; }
	void SetCommand(string cmd) { this->command = cmd; }

	bool CanThrough(CGameObject* gameObject, float collisionNx, float collisionNy);
	~CCommandPoint();
};
