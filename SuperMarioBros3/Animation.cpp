#include "Animation.h"
#include "debug.h"

CAnimation::CAnimation(int defaultFrameTime)
{
	this->defaultTime = defaultFrameTime;
	this->lastFrameTime = 0;
	this->currentFrame = 0;
	this->playScale = 1.0f;
	this->transform = new Transformation();
	this->frames.clear();
}

CAnimation::CAnimation(CAnimation* origin) : CAnimation(origin->defaultTime)
{
	this->transform->Position = origin->transform->Position;
	this->transform->Scale = origin->transform->Scale;
	this->transform->Rotation = origin->transform->Rotation;
	this->frames = vector<CAnimationFrame*>(origin->frames);
	this->lastFrameTime = origin->lastFrameTime;
	this->currentFrame = origin->currentFrame;
	this->defaultTime = origin->defaultTime;
	this->playScale = origin->playScale;
}
void CAnimation::Add(string spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	if (sprite == NULL)
		DebugOut(L"[ERROR] Sprite ID %d not found!\n", spriteId);

	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, float alpha)
{
	ULONGLONG now = GetTickCount64();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if ((now - lastFrameTime) * playScale > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, *transform, alpha);
}

