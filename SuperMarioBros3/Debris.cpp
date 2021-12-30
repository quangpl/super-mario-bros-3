#include "Debris.h"
#include "SceneManager.h"
#include "Game.h"


 Debris::Debris()
{
	 this->Animations["Default"] = CAnimations::GetInstance()->Get("ani-brick-debris");
	 this->Animations["Default"]->GetTransform()->Scale = Vec2(0.7f, 0.7f);
}
void Debris::Update(DWORD dt)
{
	vy += DEBRIS_GRAVITY * dt;
	position.x += vx * dt;
	position.y += vy * dt;

}

void Debris::Render()
{
	if (Animations.size() < 1) return;

	CAnimation* ani = Animations.begin()->second;

	Vec2 cam = SceneManager::GetInstance()->GetActiveScene()->GetCamera()->GetPosition();

	ani->GetTransform()->Position.x = position.x - cam.x + DEBRIS_SIZE / 2;
	ani->GetTransform()->Position.y = position.y - cam.y + DEBRIS_SIZE / 2;
	ani->Render(position.x, position.y);
}

void Debris::Render(int runTime, int totalTime, D3DXCOLOR overlay)
{
	if (Animations.size() < 1) return;

	CAnimation* ani = Animations.begin()->second;

	Vec2 cam = SceneManager::GetInstance()->GetActiveScene()->GetCamera()->GetPosition();

	ani->GetTransform()->Position.x = position.x - cam.x + DEBRIS_SIZE / 2;
	ani->GetTransform()->Position.y = position.y - cam.y + DEBRIS_SIZE / 2;

	ani->Render((float)runTime, (float)totalTime);
}

RectBox Debris::GetBoundingBox()
{
	return RectBox(position.x, position.y, position.x + DEBRIS_SIZE, position.y + DEBRIS_SIZE);
}
