#pragma once
#include <Windows.h>
#include "Textures.h"
#include "Sprites.h"
#include <fstream>
#include <unordered_map>
#include "constants.h"

class CMap {
	int id;
	int rows;
	int cols; 
	int rows_source; 
	int cols_source; 
	int tile_size; 
	LPCWSTR data_path; 
	LPCWSTR texture_path;
	int** tilemaps;
public:
	CMap(int id, int rows, int cols, int rows_source, int cols_source, int tile_size, LPCWSTR data_path, LPCWSTR texture_path);
	void Load();
	void Draw();
	~CMap();
};