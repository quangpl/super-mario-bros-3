#pragma once
#include "Utils.h"
#include "MapData.h"	
#include "KeyEventHandler.h"
#include "GameObject.h"
#include "Camera.h"
#include <memory>

/*
*  Abstract class for a game scene
*/
class Camera;
class CScene
{
protected:
	LPKEYEVENTHANDLER key_handler;
	string id;
	string data_path = "";
	unordered_map<DWORD, shared_ptr<CGameObject>> objects;
	shared_ptr<Camera> camera;
public: 
	Vec2 camSize = Vec2(769, 579);
	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 
	virtual void LoadObjects(const char* type, Vec2 fixedPos, Vec2 size, MapData& data) = 0;
	virtual void SetDataPath(string data_path);
	virtual void AddObject(shared_ptr<CGameObject> entity);
	virtual void AddObject(shared_ptr<CGameObject> entity, MapData& data);

	shared_ptr<Camera> GetCamera() {
		return this->camera;
	}

};
typedef CScene * LPSCENE;


class CSceneKeyHandler : public CKeyEventHandler
{
protected: 
	CScene * scence; 

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(LPSCENE s) :CKeyEventHandler() { scence = s; }
};

typedef CSceneKeyHandler* LPSCENEKEYHANDLER;