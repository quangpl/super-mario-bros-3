#include "GameObject.h"
#include "Constants.h"


#define BRICK_ANI_NORMAL		702
#define BRICK_ANI_BROKEN		703

#define BRICK_STATE_NORMAL		1
#define BRICK_STATE_BROKEN		2


class CBrick : public CGameObject
{

public:
	int brickType;
	int item;

public:
	CBrick(float x, float y, int brickType);
	~CBrick();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* colliable_objects);
	void SetState(int state);
};