#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <signal.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include "debug.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <memory>
#include "tinyXML/tinystr.h"
#include "tinyXML/tinyxml.h"

#ifndef VECTOR_0
#define VECTOR_0 Vec2(0, 0)
#endif // !VEC0
#include <D3DX10math.h>


typedef D3DXVECTOR2 Vec2;
using namespace std;

vector<string> split(string line, string delimeter = "\t");
wstring ToWSTR(string st);

LPCWSTR ToLPCWSTR(string st);