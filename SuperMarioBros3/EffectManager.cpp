#include "EffectManager.h"

CEffectManager* CEffectManager::__instance = NULL;

CEffectManager* CEffectManager::GetInstance()
{
	if (__instance == NULL) __instance = new CEffectManager();
	return __instance;
}

int CEffectManager::Add(LPEFFECT effect)
{
	int new_id = effects.size();
	if (effects[new_id] != NULL)
		DebugOut(L"[WARNING] Effect %d already exists\n", new_id);

	effects[new_id] = effect;
	return new_id;
}

LPEFFECT CEffectManager::Get(int id)
{
	LPEFFECT effect = effects[id];
	if (effect == NULL)
		DebugOut(L"[ERROR] Effect ID %d not found\n", id);
	return effect;
}

void CEffectManager::Clear()
{
	for (auto x : effects)
	{
		LPEFFECT effect = x.second;
		delete effect;
	}
	effects.clear();
}

void CEffectManager::Delete(int id)
{
	LPEFFECT effect = effects[id];
	if (effect != NULL) {
		effects.erase(id);
	}
}
