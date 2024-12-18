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
TitleScene::TitleScene(GameEngine* pGameEngine)
{
	this->pGameEngine = pGameEngine;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{

	Scene::Init();




	TitleBG* titlebg = new TitleBG(this);
	this->gameObjectArray.push_back(titlebg);


	TitleCursor* cursor = new TitleCursor(this);
	this->gameObjectArray.push_back(cursor);

	TitleLogo* titleLogo = new TitleLogo(this);
	this->gameObjectArray.push_back(titleLogo);

	MikanSoftLogo* mikanLogo = new MikanSoftLogo(this);
	this->gameObjectArray.push_back(mikanLogo);



	Camera* titleCamera = new Camera(this);
	this->gameObjectArray.push_back(titleCamera);

	BGMPlayer* bgmPlayer = new BGMPlayer(this);
	this->gameObjectArray.push_back(bgmPlayer);
	
	//他のオブジェクトを取得する可能性があるオブジェクトは後から
	//TitleManager* titleManager = new TitleManager(this);
	//this->gameObjectArray.push_back(titleManager);

	Scene::InitAllObject();

}
