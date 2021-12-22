#include "PowerMeter.h"
#include "Mario.h"
#include "Sprites.h"



PowerMeter::PowerMeter()
{
}

void PowerMeter::Update(DWORD dt)
{
	this->dt = dt;
	level = (int)CMario::GetInstance()->GetPower();
	level = min(7, max(0, level));
}

void PowerMeter::Render()
{
	float begin = position.x;
	int width = CSprites::GetInstance()->Get("spr-arrow-1")->width;
	for (int i = 1; i < 7; i++)
	{
		if (i > level) {
			CSprites::GetInstance()->Get("spr-arrow-1")->Draw(begin + width / 2, position.y + size.y / 2, trans, 1.0f);
		}
		else {
			CSprites::GetInstance()->Get("spr-arrow-0")->Draw(begin + width / 2, position.y + size.y / 2, trans, 1.0f);
		}
		begin += width;
	}

	width = CSprites::GetInstance()->Get("spr-p-icon-0")->width;
	if (level == 7 && (dt / 50) % 2) {
		CSprites::GetInstance()->Get("spr-p-icon-0")->Draw(begin + width / 2, position.y + size.y / 2, trans, 1.0f);
	}
	else {
		CSprites::GetInstance()->Get("spr-p-icon-1")->Draw(begin + width / 2, position.y + size.y / 2, trans, 1.0f);
	}
}
