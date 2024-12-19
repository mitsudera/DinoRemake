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

void StageSelectScene::Awake()
{
	Scene::Awake();

	GameObject* BG = CreateGameObject<GameObject>("BG");
	SpriteComponent* bg = BG->AddComponent<SpriteComponent>();
	bg->SetFullScreen("data/TEXTURE/stageselect/stageselect.jpg");

	GameObject* cursor = CreateGameObject<GameObject>("cursor");
	SpriteComponent* cursorSprite = cursor->AddComponent<SpriteComponent>();
	cursorSprite->SetAlphaTest(TRUE);
	cursorSprite->SetTexSlice(XMINT2(7, 1));
	cursorSprite->SetSliceTexIndex(0);


	CreateGameObject<Camera>();

	CreateGameObject<BGMPlayer>();

	CreateGameObject<StageSelectManager>();


}
