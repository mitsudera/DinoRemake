#include "TutorialManagerComponent.h"
#include "input.h"
#include "SoundSpeakerComponent.h"
#include "gameobject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameEngine.h"
TutorialManagerComponent::TutorialManagerComponent(GameObject* gameObject)
{
	this->pGameObject = gameObject;

}

TutorialManagerComponent::~TutorialManagerComponent()
{
}

void TutorialManagerComponent::Init(void)
{
	Component::Init();
	bgmPlayer = pGameObject->GetScene()->GetGameObjectName("BGMPlayer");
	bgmPlayer->GetComponent<SoundSpeakerComponent>()->LoadSound("crick.wav", "crick", SoundType::SE);
	bgmPlayer->GetComponent<SoundSpeakerComponent>()->LoadSound("kettei.wav", "kettei", SoundType::SE);


}

void TutorialManagerComponent::Uninit(void)
{
	Component::Uninit();

}

void TutorialManagerComponent::Update(void)
{
	Component::Update();

	if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_B))
	{// Enter、Bを押したら、ステージを切り替える
		bgmPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("kettei");
		pGameEngine->GetSceneManager()->SetScene(SceneManager::SCENE::STAGE_SELECT);
	}
	if (input->GetKeyboardTrigger(DIK_SPACE) || input->IsButtonTriggered(0, BUTTON_A))
	{// Spase、Aを押したら、ステージを切り替える
		bgmPlayer->GetComponent<SoundSpeakerComponent>()->StartSound("kettei");
		pGameEngine->GetSceneManager()->SetScene(SceneManager::SCENE::TITLE);

	}
}
