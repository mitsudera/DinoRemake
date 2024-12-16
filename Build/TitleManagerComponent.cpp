#include "TitleManagerComponent.h"
#include "GameEngine.h"
#include "Scene.h"
#include "input.h"
#include "SceneManager.h"
#include "transformcomponent.h"
#include "gameobject.h"
#include "Scene.h"
#include "GameEngine.h"
#include "SpriteComponent.h"

TitleManagerComponent::TitleManagerComponent(GameObject* gameObject)
{
	this->pGameObject = gameObject;
}

TitleManagerComponent::~TitleManagerComponent()
{
}

void TitleManagerComponent::Init(void)
{

	Component::Init();
	attribute = Attribute::Manager;

	titleLogo = pGameObject->GetScene()->GetGameObjectName("TitleLogo");
	titleBG = pGameObject->GetScene()->GetGameObjectName("TitleBG");
	mikanLogo= pGameObject->GetScene()->GetGameObjectName("MikanLogo");

	

}

void TitleManagerComponent::Uninit(void)
{
	Component::Uninit();
}

void TitleManagerComponent::Update(void)
{
	Component::Update();

	SceneManager* sceneManager= pGameObject->GetScene()->GetGameEngine()->GetSceneManager();


	SpriteComponent* mikanSprite = mikanLogo->GetComponent<SpriteComponent>();
	mikanLogo->SetActive(FALSE);

	if (input->GetKeyboardTrigger(DIK_SPACE))
	{
		sceneManager->SetScene(SCENE::GAME);
	}
}
