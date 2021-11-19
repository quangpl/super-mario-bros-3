#pragma once
#include "Scene.h"
#include "Utils.h"
#include <unordered_map>

class SceneManager
{
	static SceneManager* __instance;
	SceneManager();

	unordered_map<string, shared_ptr<CScene>> scenes;

	string activeSceneID;

public:
	void AddScene(string id, shared_ptr<CScene> scene);

	bool ActiveScene(string id);

	shared_ptr<CScene> GetActiveScene();

	shared_ptr<CScene> GetScene(string id);

	void Update(DWORD dt);

	void Render();

	void OnKeyDown(int key);

	void OnkeyUp(int key);

	static SceneManager* GetInstance();
	~SceneManager();
};
