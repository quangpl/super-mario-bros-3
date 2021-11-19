#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprites::Add(string id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(string id)
{
	return sprites[id];
}

/*
	Clear all loaded sprites
*/
void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}

void CSprites::Import(const char* filePath)
{
	TiXmlDocument doc(filePath);
	if (doc.LoadFile())
	{
		TiXmlElement* pRoot = doc.RootElement();

		if (pRoot)
		{
			for (TiXmlElement* sNode = pRoot->FirstChildElement("Textures"); sNode != NULL; sNode = sNode->NextSiblingElement("Textures"))
			{
				string textureId = sNode->Attribute("textureId");
				LPTEXTURE texture = CTextures::GetInstance()->Get(textureId);

				for (TiXmlElement* pNode = sNode->FirstChildElement(); pNode != nullptr; pNode = pNode->NextSiblingElement()) {
					string id = pNode->Attribute("id");

					int left = 0, top = 0, width = 0, height = 0, xPivot = 0, yPivot = 0;
					pNode->QueryIntAttribute("left", &left);
					pNode->QueryIntAttribute("top", &top);
					pNode->QueryIntAttribute("width", &width);
					pNode->QueryIntAttribute("height", &height);
					if (pNode->Attribute("xPivot") != NULL) pNode->QueryIntAttribute("xPivot", &xPivot);
					if (pNode->Attribute("yPivot") != NULL) pNode->QueryIntAttribute("yPivot", &yPivot);

					CSprites::GetInstance()->Add(id, left * 3, top * 3, width * 3, height * 3, texture);

					DebugOut(L"Load sprite: %s\n", ToLPCWSTR(id));
				}
			}
		}
	}
}