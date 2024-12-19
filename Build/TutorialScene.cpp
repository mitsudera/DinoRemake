#include "TutorialScene.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "GameEngine.h"
#include "AssetsManager.h"
#include "PostEffectShader.h"
#include "FadeShader.h"
#include "BGMPlayer.h"
#include "TutorialManager.h"
#include "SpriteComponent.h"

#define TEXTURE_TRIGGER_HEIGHT		(100.0f)			// ƒgƒŠƒK[‚Ìc‚Ì‘å‚«‚³


TutorialScene::TutorialScene(GameEngine* pGameEngine)
{
	this->pGameEngine = pGameEngine;
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Awake()
{

	Scene::Awake();


	GameObject* tutorialBG = CreateGameObject<GameObject>("tutorialBG");
	SpriteComponent* bg= tutorialBG->AddComponent<SpriteComponent>();
	bg->SetFullScreen("data/TEXTURE/tutorial/tutorial.png");


	GameObject* sousa = CreateGameObject<GameObject>("sousa");
	SpriteComponent* sousasp= sousa->AddComponent<SpriteComponent>();
	sousasp->SetSpriteCenter("data/TEXTURE/tutorial/sousa.png", XMFLOAT3(0.0f, 0.0f, 0.0f), pGameEngine->GetWindowSize().x * 0.8f, pGameEngine->GetWindowSize().y * 0.8f);
	sousasp->SetAlphaTest(TRUE);


	GameObject* trigger = CreateGameObject<GameObject>("trigger");
	SpriteComponent* triggersp= trigger->AddComponent<SpriteComponent>();
	triggersp->SetSpriteLeftDown("data/TEXTURE/tutorial/trigger.png", XMFLOAT3(0.0f, 0.0f, 0.0f), pGameEngine->GetWindowSize().x, TEXTURE_TRIGGER_HEIGHT);
	triggersp->SetAlphaTest(TRUE);


	CreateGameObject<Camera>();

	CreateGameObject<BGMPlayer>();

	CreateGameObject<TutorialManager>();
	


}
