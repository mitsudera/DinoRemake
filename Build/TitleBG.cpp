#include "TitleBG.h"
#include "SpriteComponent.h"
#include "GameEngine.h"
TitleBG::TitleBG(Scene* scene)
{
	this->pScene = scene;
}

TitleBG::~TitleBG()
{
}

void TitleBG::Awake(void)
{
	GameObject::Awake();
	this->layer = Layer::UI;

	this->name = "TitleBG";
	SpriteComponent* bg = AddComponent<SpriteComponent>();
	bg->SetSpriteLeftDown("data/texture/title/title.png", XMFLOAT3(0.0f, 0.0f, 0.0f),pGameEngine->GetWindowSize().x , pGameEngine->GetWindowSize().y);


}
