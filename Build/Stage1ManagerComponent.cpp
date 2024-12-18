#include "Stage1ManagerComponent.h"
#include "gameobject.h"
#include "ShadowMap.h"
#include "GameEngine.h"
Stage1ManagerComponent::Stage1ManagerComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}

Stage1ManagerComponent::~Stage1ManagerComponent()
{
}

void Stage1ManagerComponent::Init(void)
{
	Component::Init();
	pGameEngine->GetShadowMap()->SetEnable(TRUE);

}

void Stage1ManagerComponent::Uninit(void)
{
	Component::Uninit();
}

void Stage1ManagerComponent::Update(void)
{
	Component::Update();
}
