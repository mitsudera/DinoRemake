#include "Stage1Scene.h"
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
#include "Player.h"
#include "Stage1Manager.h"
#include "RedEnemy.h"

Stage1Scene::Stage1Scene(GameEngine* pGameEngine)
{
	this->pGameEngine = pGameEngine;
}

Stage1Scene::~Stage1Scene()
{
}

void Stage1Scene::Init()
{
	Scene::Init();


	DirectionalLight* light = new DirectionalLight(this);
	this->gameObjectArray.push_back(light);


	SkySphere* sky = new SkySphere(this);
	this->gameObjectArray.push_back(sky);
	sky->SetHasShadowAll(FALSE);

	DebugCamera* debugCamera = new DebugCamera(this);
	this->gameObjectArray.push_back(debugCamera);


	Player* player = new Player(this);
	this->gameObjectArray.push_back(player);

	RedEnemy* redEnemy = new RedEnemy(this);
	this->gameObjectArray.push_back(redEnemy);

	MeshField* field = new MeshField(this);
	this->gameObjectArray.push_back(field);




	BGMPlayer* bgmPlayer = new BGMPlayer(this);
	this->gameObjectArray.push_back(bgmPlayer);

	

	Stage1Manager* st1Manager = new Stage1Manager(this);
	this->gameObjectArray.push_back(st1Manager);

	GameManager* gameManager = new GameManager(this);
	this->gameObjectArray.push_back(gameManager);


	//ç≈å„Ç…çsÇ§
	Scene::InitAllObject();
}
