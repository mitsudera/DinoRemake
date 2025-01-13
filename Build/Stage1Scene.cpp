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
#include "Golem.h"
#include "CameraComponent.h"
#include "TextMesh.h"
#include "TextMeshComponent.h"
#include "ShadowMap.h"
#include "Tree1.h"
#include "Rock1.h"
#include "Rock3.h"
#include "Rock4.h"
#include "Rock5.h"
#include "Rock6.h"
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

	pGameEngine->GetShadowMap()->SetEnable(TRUE);

	CreateGameObject<DirectionalLight>();

	SkySphere* sky = CreateGameObject<SkySphere>();
	sky->SetHasShadowAll(FALSE);

	GameObject* dcamera = CreateGameObject<DebugCamera>();
	dcamera->GetComponent<CameraComponent>()->SetSky(GetGameObject<SkySphere>());

	pGameEngine->SetMainCamera(dcamera->GetComponent<CameraComponent>());

	CreateGameObject<MeshField>();

	CreateGameObject<Player>();

	CreateGameObject<Golem>()->GetTransFormComponent()->SetPosition(0.0f,0.0f,2000.0f);


	//tree
	CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(500.0f, 0.0f, 5000.0f);
	CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-300.0f, 0.0f, 8000.0f);

	//rock
	CreateGameObject<Rock1>()->GetTransFormComponent()->SetPosition(-2000.0f, 0.0f, 300.0f);
	CreateGameObject<Rock3>()->GetTransFormComponent()->SetPosition(-1000.0f, 0.0f, 300.0f);
	CreateGameObject<Rock4>()->GetTransFormComponent()->SetPosition(0.0f, 0.0f, 300.0f);
	CreateGameObject<Rock5>()->GetTransFormComponent()->SetPosition(1000.0f, 0.0f, 300.0f);
	CreateGameObject<Rock6>()->GetTransFormComponent()->SetPosition(2000.0f, 0.0f, 300.0f);


	CreateGameObject<GameManager>();

}
