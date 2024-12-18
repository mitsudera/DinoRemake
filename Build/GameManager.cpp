#include "GameManager.h"
#include "GameManagerComponent.h"
#include "SoundSpeakerComponent.h"
GameManager::GameManager(Scene* scene)
{
	this->pScene = scene;

}

GameManager::~GameManager()
{
}

void GameManager::Init(void)
{
	GameObject::Init();
	this->name = "GameManager";
	GameManagerComponent* gameManagerComponent = AddComponent<GameManagerComponent>();


}
