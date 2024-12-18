#include "StageSelectScene.h"
#include "TutorialScene.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "GameEngine.h"
#include "AssetsManager.h"
#include "PostEffectShader.h"
#include "FadeShader.h"
#include "BGMPlayer.h"
#include "SpriteComponent.h"
#include "StageSelectManager.h"

StageSelectScene::StageSelectScene(GameEngine* pGameEngine)
{
	this->pGameEngine = pGameEngine;
}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Init()
{
	Scene::Init();

	GameObject* BG = new GameObject(this);
	BG->Init();
	SpriteComponent* bg = BG->AddComponent<SpriteComponent>();
	bg->SetFullScreen("data/TEXTURE/stageselect/stageselect.jpg");
	BG->SetName("BG");
	this->gameObjectArray.push_back(BG);

	GameObject* cursor = new GameObject(this);
	cursor->Init();
	SpriteComponent* cursorSprite = cursor->AddComponent<SpriteComponent>();
	cursorSprite->SetAlphaTest(TRUE);
	cursorSprite->SetTexSlice(XMINT2(7, 1));
	cursorSprite->SetSliceTexIndex(0);

	cursor->SetName("cursor");
	this->gameObjectArray.push_back(cursor);

	


	Camera* tutorialCamera = new Camera(this);
	this->gameObjectArray.push_back(tutorialCamera);

	BGMPlayer* bgmPlayer = new BGMPlayer(this);
	this->gameObjectArray.push_back(bgmPlayer);

	//他のオブジェクトを取得する可能性があるオブジェクトは後から
	StageSelectManager* stageSelectManager = new StageSelectManager(this);
	this->gameObjectArray.push_back(stageSelectManager);

	Scene::InitAllObject();

}
