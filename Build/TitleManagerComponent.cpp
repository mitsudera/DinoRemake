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
#include "PostEffectShader.h"
#include "AssetsManager.h"
#include "FadeShader.h"
#include "CameraComponent.h"
#include "SoundSpeakerComponent.h"




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
	loading = pScene->GetGameObjectName("Loading");
	loading->SetActive(FALSE);
}

void TitleManagerComponent::Uninit(void)
{
	Component::Uninit();
}

void TitleManagerComponent::Update(void)
{
	Component::Update();

	if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_C) || input->IsButtonTriggered(0,BUTTON_B))
	{
		pGameEngine->GetSceneManager()->SetScene(SceneManager::SCENE::STAGE1);
		loading->SetActive(TRUE);
		pScene->GetGameObjectName("TitleLogo")->SetActive(FALSE);
		
	}


}
