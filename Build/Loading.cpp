#include "Loading.h"
#include "SpriteComponent.h"
#include "GameEngine.h"
Loading::Loading(Scene* scene)
{
	this->pScene = scene;
}

Loading::~Loading()
{
}

void Loading::Awake(void)
{
	GameObject::Awake();
	this->layer = Layer::UI;

	this->name = "Loading";
	SpriteComponent* bg = AddComponent<SpriteComponent>();
	bg->SetSpriteLeftDown("data/texture/NowLoading.png", XMFLOAT3(0.0f, 0.0f, 0.0f),pGameEngine->GetWindowSize().x , pGameEngine->GetWindowSize().y);


}
