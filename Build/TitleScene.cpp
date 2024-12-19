#include "TitleScene.h"
#include "TitleLogo.h"
#include "TitleManager.h"
#include "Camera.h"
#include "TitleBG.h"
#include "MikanSoftLogo.h"
#include "CameraComponent.h"
#include "GameEngine.h"
#include "AssetsManager.h"
#include "PostEffectShader.h"
#include "FadeShader.h"
#include "BGMPlayer.h"
#include "TitleCursor.h"
#include "TextMesh.h"
#include "TextMeshComponent.h"
#include "Text.h"
TitleScene::TitleScene(GameEngine* pGameEngine)
{
	this->pGameEngine = pGameEngine;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Awake()
{

	Scene::Awake();


	CreateGameObject<TitleBG>();

	CreateGameObject<TitleCursor>();

	CreateGameObject<TitleLogo>();

	CreateGameObject<MikanSoftLogo>();

	CreateGameObject<Camera>();

	CreateGameObject<BGMPlayer>();

	CreateGameObject<Text>();

	CreateGameObject<TitleManager>();
	TitleManager* titleManager = new TitleManager(this);
	this->gameObjectArray.push_back(titleManager);


}
