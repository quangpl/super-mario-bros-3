#pragma once
#include <windows.h>

class CEffect
{
public:

	float x = 0;
	float y = 0;

	float vx = 0;
	float vy = 0;

	CEffect(float x, float y);

	virtual void Render() = 0;
	virtual void Update(DWORD dt) = 0;
	void SetPositionX(float _x) {
		this->x = _x;
	}
	void SetPositionY(float _y) {
		this->y = _y;
	}
	float GetPositionX() {
		return this->x;
	}
	float GetPositionY() {
		return this->x;
	}
};

typedef CEffect* LPEFFECT;