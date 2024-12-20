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
#include "CameraComponent.h"
#include "TextMesh.h"
#include "TextMeshComponent.h"

Stage1Scene::Stage1Scene(GameEngine* pGameEngine)
{
	this->pGameEngine = pGameEngine;
}

Stage1Scene::~Stage1Scene()
{
}

void Stage1Scene::Awake()
{
	Scene::Awake();


	CreateGameObject<DirectionalLight>();

	SkySphere* sky=CreateGameObject<SkySphere>();
	sky->SetHasShadowAll(FALSE);

	GameObject* dcamera= CreateGameObject<DebugCamera>();
	dcamera->GetComponent<CameraComponent>()->SetSky(GetGameObject<SkySphere>());

	CreateGameObject<Player>();

	CreateGameObject<RedEnemy>();

	CreateGameObject<MeshField>();

	CreateGameObject<BGMPlayer>();

	CreateGameObject<Stage1Manager>();

	CreateGameObject<GameManager>();




}
