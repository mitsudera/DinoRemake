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

void MikanSoftLogo::Init(void)
{
	GameObject::Init();
	this->layer = Layer::UI;

	this->name = "MikanLogo";
	SpriteComponent* logo = AddComponent<SpriteComponent>();
	logo->CreateVertexBuffer();
	logo->SetSpriteLeftTop("data/texture/title/logo.png", XMFLOAT3(0.0f, 0.0f, 0.0f), pGameEngine->GetWindowSize().x, pGameEngine->GetWindowSize().y);

}
