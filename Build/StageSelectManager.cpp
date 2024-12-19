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
	this->name = "StageSelectManager";
	AddComponent<StageSelectManagerComponent>();
}
