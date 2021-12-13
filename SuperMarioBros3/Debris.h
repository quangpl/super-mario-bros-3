#include "Animation.h"
#include "GameObject.h"
#include "Animations.h"
#define DEBRIS_GRAVITY  0.002f
#define DEBRIS_SIZE  12

class Debris : public CGameObject
{
public:
	Debris();
	unordered_map<string, CAnimation*> Animations;
public:
	virtual void Update(DWORD dt);

	virtual void Render();

	virtual void Render(int runTime, int totalTime, D3DXCOLOR overlay);

	virtual RectBox GetBoundingBox();
};

