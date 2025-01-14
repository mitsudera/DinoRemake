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
#include "InvisibleWall.h"
#include "BoxColliderComponent.h"
#include "SoundSpeakerComponent.h"
#include "Bear.h"
#include "Loading.h"
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

	CreateGameObject<Bear>()->GetTransFormComponent()->SetPosition(0.0f,0.0f,200.0f);


	//tree
	{
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-3645.0f, 0.0f, 5638.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-1996.0f, 0.0f, 2905.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(2987.0f, 0.0f, -7111.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(1221.0f, 0.0f, 6019.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(4163.0f, 0.0f, -6402.0f);

		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(219.0f, 0.0f, 2879.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-1984.0f, 0.0f, -5502.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(6705.0f, 0.0f, -6216.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(5642.0f, 0.0f, 7467.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-4462.0f, 0.0f, 4634.0f);


		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-408.0f, 0.0f, -227.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(392.0f, 0.0f, 1954.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(470.0f, 0.0f, -2246.0f);
		CreateGameObject<Tree1>()->GetTransFormComponent()->SetPosition(-2946.0f, 0.0f, 844.0f);

	}


	
	//rock
	{
		TransformComponent* rt = CreateGameObject<Rock1>()->GetTransFormComponent();
		rt->SetPosition(300.0f, 0.0f, 300.0f);

	}


		
		
		
		
		
		
		
		
	float fieldSize = 1024.0f * 16.0f * 0.5;




	
	GameObject* iw1 = CreateGameObject<InvisibleWall>();
	iw1->GetTransFormComponent()->SetPosition(0.0f, 0.0f, fieldSize);
	iw1->GetComponent<BoxColliderComponent>()->SetBox(fieldSize * 2.0f, 10000.0f, 1000.0f);

	GameObject* iw2 = CreateGameObject<InvisibleWall>();
	iw2->GetTransFormComponent()->SetPosition(0.0f, 0.0f, -fieldSize);
	iw2->GetComponent<BoxColliderComponent>()->SetBox(fieldSize * 2.0f, 10000.0f, 1000.0f);

	GameObject* iw3 = CreateGameObject<InvisibleWall>();
	iw3->GetTransFormComponent()->SetPosition(fieldSize, 0.0f, 0.0f);
	iw3->GetComponent<BoxColliderComponent>()->SetBox(1000.0f, 10000.0f, fieldSize * 2.0f);

	GameObject* iw4 = CreateGameObject<InvisibleWall>();
	iw4->GetTransFormComponent()->SetPosition(-fieldSize, 0.0f, 0.0f);
	iw4->GetComponent<BoxColliderComponent>()->SetBox(1000.0f, 10000.0f, fieldSize * 2.0f);


	SoundSpeakerComponent* speaker= CreateGameObject<BGMPlayer>()->GetComponent<SoundSpeakerComponent>();
	speaker->LoadSound("stage1bgm.wav", "BGM", SoundType::BGM);
	speaker->StartSound("BGM");


	CreateGameObject<Loading>()->SetActive(FALSE);

	CreateGameObject<GameManager>();



}
