#include "TutorialManager.h"
#include "TutorialManagerComponent.h"

TutorialManager::TutorialManager(Scene* scene)
{
	pScene = scene;
}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::Awake(void)
{
	GameObject::Awake();
	this->name = "TutorialManager";
	AddComponent<TutorialManagerComponent>();

}
