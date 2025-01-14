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

	float texHeight = (158.0f/1080.0f)*2.0f;
	float texWidth = (565.0f/1980.0f)*2.0f;

	XMFLOAT2 windowsize = pGameEngine->GetWindowSize();
	logo->SetSpriteCenter("data/texture/TitleLogo.png", XMFLOAT3(0.0f, ((450.0f / 1080.0f) * windowsize.y), 0.0f), texWidth * windowsize.x, texHeight * windowsize.y);

}
