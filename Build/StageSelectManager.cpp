#include "StageSelectManager.h"
#include "StageSelectManagerComponent.h"
StageSelectManager::StageSelectManager(Scene* scene)
{
	pScene = scene;
}

StageSelectManager::~StageSelectManager()
{
}

void StageSelectManager::Init(void)
{
	GameObject::Init();
	this->name = "StageSelectManager";
	AddComponent<StageSelectManagerComponent>();
}
