#include "TitleScene.h"
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
#include "InvisibleWall.h"
#include "BoxColliderComponent.h"
#include "SoundSpeakerComponent.h"
#include "Bear.h"
#include "TitleManager.h"
#include "TitlePlayer.h"
#include "TitleLogo.h"
#include "Loading.h"
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


	pGameEngine->GetShadowMap()->SetEnable(TRUE);

	CreateGameObject<DirectionalLight>();

	SkySphere* sky = CreateGameObject<SkySphere>();
	sky->SetHasShadowAll(FALSE);

	GameObject* cam = CreateGameObject<Camera>();
	CameraComponent* camcom = cam->GetComponent<CameraComponent>();
	camcom->SetSky(GetGameObject<SkySphere>());
	camcom->SetFar(10000.0f);

	pGameEngine->SetMainCamera(cam->GetComponent<CameraComponent>());

	cam->GetTransFormComponent()->SetPosition(0.0f, 400.0f, 0.0f);
	cam->GetTransFormComponent()->SetRotation(XM_PIDIV4*0.3f, 0.0f, 0.0f);

	CreateGameObject<MeshField>();

	GameObject* tp = CreateGameObject<TitlePlayer>();


	//tree
	{

		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(642.0f, 0.0f, 467.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-462.0f, 0.0f, 634.0f);


		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-508.0f, 0.0f, 5227.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(692.0f, 0.0f, 1054.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(870.0f, 0.0f, 1246.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-2946.0f, 0.0f, 4844.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-418.0f, 0.0f, 3227.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(642.0f, 0.0f, 6054.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(920.0f, 0.0f, 1246.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-818.0f, 0.0f, 227.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(592.0f, 0.0f, 1054.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(670.0f, 0.0f, 1246.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-1046.0f, 0.0f, 844.0f);

	}



	//rock
	{
		TransformComponent* rt = CreateGameObject<Rock1>()->GetTransFormComponent();
		rt->SetPosition(300.0f, 0.0f, 300.0f);

	}





	SoundSpeakerComponent* speaker = CreateGameObject<BGMPlayer>()->GetComponent<SoundSpeakerComponent>();
	speaker->LoadSound("titlebgm.wav", "BGM", SoundType::BGM);
	speaker->StartSound("BGM");


	CreateGameObject<BGMPlayer>();

	CreateGameObject<TitleLogo>();

	CreateGameObject<Loading>()->SetActive(FALSE);
	CreateGameObject<TitleManager>();


}
