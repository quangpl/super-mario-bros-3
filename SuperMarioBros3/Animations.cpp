#include "Animations.h"
#include "debug.h"

CAnimations* CAnimations::__instance = NULL;

CAnimations* CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(string id, LPANIMATION ani)
{
	if (animations[id] != NULL)
		DebugOut(L"[WARNING] Animation %d already exists\n", id);

	animations[id] = ani;
}

void CAnimations::Import(const char* filePath) {
	TiXmlDocument doc(filePath);
	if (doc.LoadFile())
	{
		TiXmlElement* pRoot = doc.RootElement();

		if (pRoot)
		{
			TiXmlElement* pObj = pRoot->FirstChildElement();

			DebugOut(L"Object ID: %s\n", ToLPCWSTR(pObj->Attribute("gameObjectId")));
			DebugOut(L"Texture ID: %s\n", ToLPCWSTR(pObj->Attribute("textureId")));

			for (TiXmlElement* aniNode = pObj->FirstChildElement(); aniNode != nullptr; aniNode = aniNode->NextSiblingElement()) {
				int animationDefaultFrameTime = 100;
				aniNode->QueryIntAttribute("frameTime", &animationDefaultFrameTime);

				CAnimation* ani = new CAnimation(animationDefaultFrameTime);

				for (TiXmlElement* spriteNode = aniNode->FirstChildElement(); spriteNode != nullptr; spriteNode = spriteNode->NextSiblingElement()) {
					string id = spriteNode->Attribute("id");

					int frameTime = 0;
					spriteNode->QueryIntAttribute("frameTime", &frameTime);

					CSprite* sprite = CSprites::GetInstance()->Get(id);

					ani->Add(id, frameTime);
				}

				this->Add(aniNode->Attribute("aniId"), ani);
				DebugOut(L"Animation loaded. Id = %s\n", ToLPCWSTR(aniNode->Attribute("aniId")));
			}
		}
	}
	else
	{
		DebugOut(L"Failed to load file \"%s\"\n", ToLPCWSTR(filePath));
	}
}
LPANIMATION CAnimations::Get(string id)
{
	LPANIMATION ani = animations[id];
	if (ani == NULL)
		DebugOut(L"[ERROR] Animation ID %d not found\n", id);
	return ani;
}

void CAnimations::Clear()
{
	for (auto x : animations)
	{
		LPANIMATION ani = x.second;
		delete ani;
	}

	animations.clear();
}
