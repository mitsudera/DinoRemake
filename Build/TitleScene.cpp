#include "TitleScene.h"
#include "TitleLogo.h"
#include "TitleManager.h"
#include "Camera.h"
#include "TitleBG.h"
#include "MikanSoftLogo.h"
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

	TitleLogo* titleLogo = new TitleLogo(this);
	this->gameObjectArray.push_back(titleLogo);

	MikanSoftLogo* mikanLogo = new MikanSoftLogo(this);
	this->gameObjectArray.push_back(mikanLogo);

	Camera* titleCamera = new Camera(this);
	this->gameObjectArray.push_back(titleCamera);



	//���̃I�u�W�F�N�g���擾����\��������I�u�W�F�N�g�͌ォ��
	TitleManager* titleManager = new TitleManager(this);
	this->gameObjectArray.push_back(titleManager);

	Scene::InitAllObject();

}
