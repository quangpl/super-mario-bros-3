#pragma once
#include "Scene.h"
#include "Utils.h"
#include <unordered_map>

class SceneManager
{
	static SceneManager* __instance;
	SceneManager();

	unordered_map<string, CScene*> scenes;

	string activeSceneID;

public:
	void AddScene(string id, CScene* scene);

	bool ActiveScene(string id);

	CScene* GetActiveScene();

	CScene* GetScene(string id);

	void Update(DWORD dt);

	void Render();

	void OnKeyDown(int key);

	void OnkeyUp(int key);

	static SceneManager* GetInstance();
	~SceneManager();
};
