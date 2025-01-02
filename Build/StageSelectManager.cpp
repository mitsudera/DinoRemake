#include "StageSelectManager.h"
#include "StageSelectManagerComponent.h"
StageSelectManager::StageSelectManager(Scene* scene)
{
	pScene = scene;
}

StageSelectManager::~StageSelectManager()
{
}

void StageSelectManager::Awake(void)
{
	GameObject::Awake();
	SetName("StageSelectManager");
	AddComponent<StageSelectManagerComponent>();
}
