#include "Sprite.h"
#include "Game.h"

CSprite::CSprite(string id, int left, int top, int width, int height, int xPivot, int yPivot, LPTEXTURE texture)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->pivot = D3DXVECTOR3((float)xPivot, (float)yPivot, 0);
	this->texture = texture;
}

void CSprite::Draw(float x, float y, Transformation& transform, float alpha)
{
	Camera* camera = SceneManager::GetInstance()->GetActiveScene()->GetCamera();
	CGame* g = CGame::GetInstance();
	float cx = camera->GetPosition().x;
	float cy = camera->GetPosition().y;
	RECT r;

	r.left = this->left;
	r.top = this->top;
	r.right = this->left + this->width;
	r.bottom = this->top + this->height;
	CGame::GetInstance()->Draw(x - cx, y - cy, pivot, this->texture, r, transform, alpha);
}

void CSprite::DrawWithoutCamera(float x, float y, Transformation& transform, float alpha)
{

	CGame* g = CGame::GetInstance();
	RECT r;
	r.left = this->left;
	r.top = this->top;
	r.right = this->left + this->width;
	r.bottom = this->top + this->height;
	CGame::GetInstance()->Draw(x, y, pivot, this->texture, r, transform, alpha);
}

