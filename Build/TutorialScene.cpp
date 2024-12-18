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

#define TEXTURE_TRIGGER_HEIGHT		(100.0f)			// トリガーの縦の大きさ


TutorialScene::TutorialScene(GameEngine* pGameEngine)
{
	this->pGameEngine = pGameEngine;
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Init()
{

	Scene::Init();

	GameObject* tutorialBG = new GameObject(this);
	tutorialBG->Init();
	SpriteComponent* bg= tutorialBG->AddComponent<SpriteComponent>();
	bg->SetFullScreen("data/TEXTURE/tutorial/tutorial.png");
	tutorialBG->SetName("tutorialBG");
	this->gameObjectArray.push_back(tutorialBG);


	GameObject* sousa = new GameObject(this);
	sousa->Init();
	SpriteComponent* sousasp= sousa->AddComponent<SpriteComponent>();
	sousasp->SetSpriteCenter("data/TEXTURE/tutorial/sousa.png", XMFLOAT3(0.0f, 0.0f, 0.0f), pGameEngine->GetWindowSize().x * 0.8f, pGameEngine->GetWindowSize().y * 0.8f);
	sousasp->SetAlphaTest(TRUE);
	sousa->SetName("sousa");
	this->gameObjectArray.push_back(sousa);


	GameObject* trigger = new GameObject(this);
	trigger->Init();
	SpriteComponent* triggersp= trigger->AddComponent<SpriteComponent>();
	triggersp->SetSpriteLeftDown("data/TEXTURE/tutorial/trigger.png", XMFLOAT3(0.0f, 0.0f, 0.0f), pGameEngine->GetWindowSize().x, TEXTURE_TRIGGER_HEIGHT);
	triggersp->SetAlphaTest(TRUE);
	trigger->SetName("trigger");
	this->gameObjectArray.push_back(trigger);




	Camera* tutorialCamera = new Camera(this);
	this->gameObjectArray.push_back(tutorialCamera);

	BGMPlayer* bgmPlayer = new BGMPlayer(this);
	this->gameObjectArray.push_back(bgmPlayer);
	
	//他のオブジェクトを取得する可能性があるオブジェクトは後から
	TutorialManager* tutorialManager = new TutorialManager(this);
	this->gameObjectArray.push_back(tutorialManager);

	Scene::InitAllObject();

}
