#pragma once
#include "Map.h"

CMap::CMap(int id, int rows, int cols, int rows_source, int cols_source, int tile_size, LPCWSTR data_path, LPCWSTR texture_path)
{
	this->id = id;
	this->rows = rows;
	this->cols = cols;
	this->rows_source = rows_source;
	this->cols_source = cols_source;
	this->tile_size = tile_size;
	this->data_path = data_path;
	this->texture_path = texture_path;
	this->tilemaps = new int* [rows]; 
	for (int i = 0; i < rows; i++)
	{
		this->tilemaps[i] = new int[cols];
	}
};

void CMap::Load()
{
	CTextures* textures = CTextures::GetInstance();
	textures->Add(this->id, this->texture_path);
	CSprites* sprites = CSprites::GetInstance();
	LPTEXTURE texMap = textures->Get(this->id);

	int spriteId = 1;
	for (UINT i = 0; i < this->rows_source; i++)
	{
		for (UINT j = 0; j < this->cols_source; j++)
		{
			sprites->Add(spriteId + this->id, this->tile_size * j, this->tile_size * i, this->tile_size * (j + 1) - 1, this->tile_size * (i + 1) - 1, texMap); // from 0 to 5 have six numbers 
			spriteId = spriteId + 1;
		}
	}

	ifstream f;
	f.open(this->data_path);
	if (f.fail())
	{
		f.close();
		return;
	}
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
			f >> tilemaps[i][j];
	}

	f.close();
}

void CMap::Draw() {
	// TODO : Need improve with dynamic map and keep follow mario
	int firstCol = 0;
	int lastCol = firstCol + (SCREEN_WIDTH / this->tile_size);
	CSprites* sprites = CSprites::GetInstance();
	for (int i = 0; i < rows; i++)
	{
		for (int j = firstCol; j <= lastCol; j++)
		{
			float x = (int)this->tile_size * (j - firstCol);
			float y = (int)this->tile_size * i;

			sprites->Get(tilemaps[i][j] + this->id)->Draw(x, y);
		}
	}
}
CMap::~CMap()
{
	for (int i = 0; i < this->rows; i++)
	{
		delete[] this->tilemaps[i];
	}
	delete[] tilemaps;
}
