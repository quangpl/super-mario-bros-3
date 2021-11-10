#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Koopas.h"
#define ACTIVATION_POINT_WIDTH 16
#define ACTIVATION_POINT_HEIGHT 16

enum ActivationCommand
{
	TurnKoopasAround = 1,
};


class CActivationPoint :public CGameObject
{
	int width;
	int height;
	int command;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	CActivationPoint(int w, int h, int command);

	int GetCommand() { return this->command; }
	void SetCommand(int cmd) { this->command = cmd; }

	bool CanThrough(CGameObject* gameObject, float collisionNx, float collisionNy);
	~CActivationPoint();
};
