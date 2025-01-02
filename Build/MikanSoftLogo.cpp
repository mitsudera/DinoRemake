#include "MikanSoftLogo.h"
#include "GameEngine.h"
#include "Scene.h"

MikanSoftLogo::MikanSoftLogo(Scene* scene)
{
	this->pScene = scene;

}

MikanSoftLogo::~MikanSoftLogo()
{
}

void MikanSoftLogo::Awake(void)
{
	GameObject::Awake();
	this->layer = Layer::UI;
	
	SetName("MikanLogo");
	SpriteComponent* logo = AddComponent<SpriteComponent>();
	logo->SetSpriteLeftDown("data/texture/title/logo.png", XMFLOAT3(0.0f, 0.0f, 0.0f), pGameEngine->GetWindowSize().x, pGameEngine->GetWindowSize().y);

}
