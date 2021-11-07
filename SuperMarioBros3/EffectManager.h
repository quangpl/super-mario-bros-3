#include <unordered_map>
#include "Effect.h"
#include "debug.h"

class CEffectManager
{
	static CEffectManager* __instance;
	unordered_map<int, LPEFFECT> effects;

public:
	int Add(LPEFFECT effect);
	LPEFFECT Get(int id);
	void Delete(int id);
	void Clear();
	unordered_map<int, LPEFFECT> GetAll() { return this->effects; }
	static CEffectManager* GetInstance();
};
