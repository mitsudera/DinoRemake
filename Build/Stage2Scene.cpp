#include "Stage2Scene.h"
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


Stage2Scene::Stage2Scene(GameEngine* pGameEngine)
{
	this->pGameEngine = pGameEngine;
}

Stage2Scene::~Stage2Scene()
{
}

void Stage2Scene::Awake()
{
	Scene::Awake();


	CreateGameObject<DirectionalLight>();

	SkySphere* sky = CreateGameObject<SkySphere>();
	sky->SetHasShadowAll(FALSE);

	CreateGameObject<DebugCamera>();

	CreateGameObject<MeshField>();

	CreateGameObject<BGMPlayer>();


	CreateGameObject<GameManager>();


}
