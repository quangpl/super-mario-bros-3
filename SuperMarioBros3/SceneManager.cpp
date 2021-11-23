#include "SceneManager.h"

SceneManager* SceneManager::__instance = nullptr;

void SceneManager::AddScene(string id, CScene* scene)
{
	if (!scene) return;
	scenes[id] = scene;
}

bool SceneManager::ActiveScene(string id)
{
	if (scenes.find(id) == scenes.end()) return false;

	if (GetActiveScene() != nullptr) {
		GetActiveScene()->Unload();
	}

	activeSceneID = id;
	GetActiveScene()->Load();
	return true;
}

CScene* SceneManager::GetActiveScene()
{
	if (scenes.find(activeSceneID) == scenes.end()) return nullptr;
	return scenes.at(activeSceneID);
}

CScene* SceneManager::GetScene(string id)
{
	if (scenes.find(id) == scenes.end()) return nullptr;
	return scenes.at(id);
}

void SceneManager::Update(DWORD dt)
{
	GetActiveScene()->Update(dt);
}

void SceneManager::Render()
{
	GetActiveScene()->Render();
}

void SceneManager::OnKeyDown(int key)
{
	/*shared_ptr<CScene> s = GetActiveScene();
	if (s != NULL) {
		s->OnKeyDown(key);
	}*/
}

void SceneManager::OnkeyUp(int key)
{
	/*shared_ptr<CScene> s = GetActiveScene();
	if (s != NULL) {
		s->OnKeyUp(key);
	}*/
}

SceneManager* SceneManager::GetInstance()
{
	if (__instance == nullptr) {
		__instance = new SceneManager();
	}
	return __instance;
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
