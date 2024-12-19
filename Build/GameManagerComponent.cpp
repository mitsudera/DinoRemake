#include "GameManagerComponent.h"
#include "GameScene.h"
#include "gameobject.h"
#include "GameEngine.h"
#include "input.h"
#include "CameraComponent.h"
#include "ShadowMap.h"
#include "transformcomponent.h"
#include "PlayerComponent.h"

GameManagerComponent::GameManagerComponent(GameObject* gameObject)
{
	this->pGameObject = gameObject;
}

GameManagerComponent::~GameManagerComponent()
{
}

void GameManagerComponent::Awake(void)
{
	Component::Awake();
	attribute = Attribute::Manager;


	pGameEngine->GetShadowMap()->SetEnable(TRUE);
	pGameEngine->GetShadowMap()->SetVariance(TRUE);

}

void GameManagerComponent::Init(void)
{
	this->gameScene = pGameObject->GetScene();
	this->gameCamera = gameScene->GetGameObjectName("Player")->GetChild("Camera")->GetComponent<CameraComponent>();
	this->debugCamera = gameScene->GetGameObjectName("DebugCamera")->GetComponent<CameraComponent>();
	this->player = gameScene->GetGameObjectName("Player");
	pGameEngine->GetShadowMap()->SetEnable(TRUE);
	SetCameraModeGame();


}

void GameManagerComponent::Uninit(void)
{
	Component::Uninit();
}

void GameManagerComponent::Update(void)
{
	Component::Update();
	if(input->GetKeyboardTrigger(DIK_P))
	{
		SetCameraModeGame();
	}
	if(input->GetKeyboardTrigger(DIK_O))
	{
		SetCameraModeDebug();
	}




}

void GameManagerComponent::SetCameraModeGame(void)
{
	gameCamera->SetActive(TRUE);
	gameCamera->SetMainCamera();
	debugCamera->SetActive(FALSE);
	player->GetComponent<PlayerComponent>()->SetContorol(TRUE);

	//pGameObject->GetScene()->GetGameObjectName("Robot")->GetComponent<RobotComponent>()->SetActive(TRUE);


}

void GameManagerComponent::SetCameraModeDebug(void)
{
	gameCamera->SetActive(FALSE);
	debugCamera->SetActive(TRUE);
	debugCamera->GetTransFormComponent()->SetPosition(gameCamera->GetTransFormComponent()->GetWorldPos());
	player->GetComponent<PlayerComponent>()->SetContorol(FALSE);
	debugCamera->SetMainCamera();
	//pGameObject->GetScene()->GetGameObjectName("Robot")->GetComponent<RobotComponent>()->SetActive(FALSE);

}

