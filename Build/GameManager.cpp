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

void GameManager::Awake(void)
{
	GameObject::Awake();
	SetName("GameManager");
	GameManagerComponent* gameManagerComponent = AddComponent<GameManagerComponent>();


}
