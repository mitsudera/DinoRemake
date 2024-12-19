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

void TitleLogo::Awake(void)
{
	GameObject::Awake();
	this->layer = Layer::UI;

	this->name = "TitleLogo";
	SpriteComponent* logo = AddComponent<SpriteComponent>();
	logo->SetAlphaTest(TRUE);

	XMFLOAT2 windowsize = pGameEngine->GetWindowSize();
	logo->SetSpriteCenter("data/texture/title/titlelogo.png", XMFLOAT3(0.0f, ((450.0f / 1080.0f) * windowsize.y), 0.0f), (1200.0f / 1920.0f) * windowsize.x, (600.0f / 1080.0f) * windowsize.y);


}
