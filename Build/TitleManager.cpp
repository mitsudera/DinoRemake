#include "TitleManager.h"
#include "TitleManagerComponent.h"

TitleManager::TitleManager(Scene* scene)
{
	this->pScene = scene;
}

TitleManager::~TitleManager()
{
}

void TitleManager::Awake(void)
{
	GameObject::Awake();
	this->name = "TitleManager";
	TitleManagerComponent* titleManager = AddComponent<TitleManagerComponent>();


}
