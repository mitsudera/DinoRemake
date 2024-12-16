#include "GameScene.h"
#include "GameManager.h"
#include "Camera.h"
#include "DebugCamera.h"
#include "SkySphere.h"
#include "MeshComponent.h"
#include "DirectionalLightComponent.h"
#include "LightManager.h"
#include "transformcomponent.h"
#include "DirectionalLight.h"
#include "GameEngine.h"
#include "AssetsManager.h"
#include "BGMPlayer.h"
#include "MeshField.h"

GameScene::GameScene(GameEngine* pGameEngine)
{
	this->pGameEngine = pGameEngine;
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	Scene::Init();


	DirectionalLight* light = new DirectionalLight(this);
	this->gameObjectArray.push_back(light);


	SkySphere* sky = new SkySphere(this);
	this->gameObjectArray.push_back(sky);
	sky->SetHasShadowAll(FALSE);






	MeshField* field = new MeshField(this);
	this->gameObjectArray.push_back(field);


	DebugCamera* debugCamera=new DebugCamera(this);
	this->gameObjectArray.push_back(debugCamera);


	BGMPlayer* bgmPlayer = new BGMPlayer(this);
	this->gameObjectArray.push_back(bgmPlayer);


	//���̃I�u�W�F�N�g���擾����\��������I�u�W�F�N�g�͌ォ��
	GameManager* gameManager = new GameManager(this);
	this->gameObjectArray.push_back(gameManager);



	//�Ō�ɍs��
	Scene::InitAllObject();
}
