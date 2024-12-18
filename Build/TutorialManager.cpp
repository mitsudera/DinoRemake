#include "TutorialManager.h"
#include "TutorialManagerComponent.h"

TutorialManager::TutorialManager(Scene* scene)
{
	pScene = scene;
}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::Init(void)
{
	GameObject::Init();
	this->name = "TutorialManager";
	AddComponent<TutorialManagerComponent>();

}
