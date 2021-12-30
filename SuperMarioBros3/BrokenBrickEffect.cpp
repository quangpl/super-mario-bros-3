#include "BrokenBrickEffect.h"

BrokenBrickEffect::BrokenBrickEffect(Vec2 pos) : CEffect(pos.x, pos.y)
{
	this->startTime = 0;
	for (int i = 0; i < 4; i++)
	{
		Debris* debris = new Debris();
		debris->position = pos;

		switch (i)
		{
		case 0:
			debris->vx = (float)0.3 * 0.5;
			debris->vy = (float)-1.3 * 0.5;
			break;
		case 1:
			debris->vx = (float)0.3 * 0.5;
			debris->vy = (float)-0.5 * 0.5;
			break;
		case 2:
			debris->vx = (float)-0.3 * 0.5;
			debris->vy = (float)-0.5 * 0.5;
			break;
		case 3:
			debris->vx = (float)-0.3 * 0.5;
			debris->vy = (float)-1.3 * 0.5;
			break;
		}

		this->debrises.push_back(debris);
	}
}

void BrokenBrickEffect::Render()
{
	for (int i = 0; i < (int)this->debrises.size(); i++) {
		this->debrises[i]->Render();
	}
}

void BrokenBrickEffect::Update(DWORD dt)
{
	for (int i = 0; i < (int)this->debrises.size(); i++) {
		this->debrises[i]->Update(dt);
	}
}


void BrokenBrickEffect::Start(function<void()> _callback)
{

}
