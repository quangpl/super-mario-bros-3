#include "Sprite.h"

CSprite::CSprite(string id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

void CSprite::Draw(float x, float y)
{
	CGame* g = CGame::GetInstance();
	float cx, cy;
	g->GetCamPos(cx, cy);

	cx = (FLOAT)floor(cx);
	cy = (FLOAT)floor(cy);
	
	x = (FLOAT)floor(x);
	y = (FLOAT)floor(y);

	g->Draw(x - cx, y - cy, this->texture, this->left, this->top, this->right,this->bottom, 1);
}

