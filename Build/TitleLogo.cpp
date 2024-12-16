#include "TitleLogo.h"
#include "SpriteComponent.h"
#include "GameEngine.h"
TitleLogo::TitleLogo(Scene* scene)
{
	this->pScene = scene;
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Init(void)
{
	GameObject::Init();
	this->layer = Layer::UI;

	this->name = "TitleLogo";
	SpriteComponent* logo = new SpriteComponent(this);
	logo->Init();
	logo->CreateVertexBuffer();

	XMFLOAT2 windowsize = pGameEngine->GetWindowSize();
	logo->SetSpriteCenter("data/texture/title/titlelogo.png", XMFLOAT3(0.0f, ((300.0f / 1080.0f) * windowsize.y), 0.0f), (600.0f / 1920.0f) * windowsize.x, (300.0f / 1080.0f) * windowsize.y);
	this->componentList.push_back(logo);


}
