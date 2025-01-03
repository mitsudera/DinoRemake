#include "SkinMeshTest.h"
#include "transformcomponent.h"
#include "AnimationControlerComponent.h"
#include "MoveTestComponent.h"
#include "CapsuleColliderComponent.h"
#include "RigidBodyComponent.h"
#include "CameraComponent.h"
#include "Scene.h"
#include "GameEngine.h"
#include "renderer.h"
#include "SkySphere.h"
SkinMeshTest::SkinMeshTest(Scene* scene)
{
	pScene = scene;
}

SkinMeshTest::~SkinMeshTest()
{
}

void SkinMeshTest::Awake(void)
{
	GameObject::Awake();
	this->name = "Player";
	this->transformComponent->SetPosition(XMFLOAT3(0.0f, 10.0f, 0.0f));
	this->transformComponent->SetScale(XMFLOAT3(0.1f, 0.1f, 0.1f));
	//this->transformComponent->RotWorldYaw(XM_PIDIV2);

	this->LoadFbxFileSkinMesh("aqchan.fbx");

	AnimationControlerComponent* animControler = this->AddComponent<AnimationControlerComponent>();
	animControler->LoadDefaulAnimation("AQIdol.fbx", "Idol");
	animControler->LoadAnimation("AQJump.fbx", "Jump", FALSE);
	animControler->LoadAnimation("AQFallIdol.fbx", "FallIdol", TRUE);
	AnimParameter para;
	para.value = FALSE;
	para.isTrigger = TRUE;
	animControler->CreateCondition("JumpTrigger", para);
	animControler->CreateTransition("Idol", "Jump", "JumpTrigger", TRUE);
	animControler->CreateNotLoopAnimExitTransition("Jump", "FallIdol");
	para.value = TRUE;
	para.isTrigger = FALSE;
	animControler->CreateCondition("OnGround", para);
	animControler->CreateTransition("Idol", "FallIdol", "OnGround", FALSE);
	animControler->CreateTransition("FallIdol", "Idol", "OnGround", TRUE);

	AddComponent<CapsuleColliderComponent>();

	AddComponent<RigidBodyComponent>();

	AddComponent<MoveTestComponent>();


	//子オブジェクトとしてカメラを作成
	{
		//ゲームオブジェクト生成
		GameObject* child = AddChild("Camera");
		child->GetTransFormComponent()->SetPosition(XMFLOAT3(0.0f, 200.0f, -400.0f));

		//カメラコンポーネントの生成
		CameraComponent* cameraComponent = child->AddComponent<CameraComponent>();
		cameraComponent->Init();
		cameraComponent->SetRenderTarget(pScene->GetGameEngine()->GetRenderer()->GetBackBuffer());
		cameraComponent->SetDepthStencilView(pScene->GetGameEngine()->GetRenderer()->GetBackBufferDSV());
		cameraComponent->SetSky(pScene->GetGameObject<SkySphere>());
		cameraComponent->SetTrackingMode(CameraComponent::TrackingMode::PARENT);
		cameraComponent->SetNear(1.0f);
		cameraComponent->SetFar(1000.0f);

		//エンジンのメインカメラにセット
		pGameEngine->SetMainCamera(cameraComponent);

	}

}
