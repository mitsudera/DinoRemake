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
#include "PlayerAnimationControlComponent.h"
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

	this->LoadFbxFileSkinMesh("Player2.fbx");

	AnimationControlerComponent* animControler = this->AddComponent<AnimationControlerComponent>();
	animControler->LoadDefaulAnimation("PlayerIdle.fbx", "Idle");
	animControler->LoadAnimation("PlayerWalk.fbx", "Walk", TRUE);
	animControler->LoadAnimation("PlayerRun.fbx", "Run", TRUE);
	animControler->LoadAnimation("PlayerJump.fbx", "Jump", FALSE);
	animControler->LoadAnimation("PlayerFallIdle.fbx", "FallIdle", TRUE);

	//アニメーショントランジション用パラメータの設定
	//bool
	AnimParameter para;
	para.value = FALSE;
	para.isTrigger = FALSE;
	animControler->CreateCondition("Walk", para);
	animControler->CreateCondition("Run", para);
	animControler->CreateCondition("OnGround", para);

	//trigger
	para.value = FALSE;
	para.isTrigger = TRUE;
	animControler->CreateCondition("JumpTrigger", para);


	//トランジションの設定
	//idolからの移行
	animControler->CreateTransition("Idle", "Walk", "Walk", TRUE);
	animControler->CreateTransition("Idle", "Run", "Run", TRUE);
	animControler->CreateTransition("Idle", "Jump", "JumpTrigger", TRUE);
	animControler->CreateTransition("Idle", "FallIdle", "OnGround", FALSE);

	//walkからの移行
	animControler->CreateTransition("Walk", "Idle", "Walk", FALSE);
	animControler->CreateTransition("Walk", "Run", "Run", TRUE);
	animControler->CreateTransition("Walk", "Jump", "JumpTrigger", TRUE);
	animControler->CreateTransition("Walk", "FallIdle", "OnGround", FALSE);

	//Runからの移行
	animControler->CreateTransition("Run", "Walk", "Walk", TRUE);
	animControler->CreateTransition("Run", "Idle", "Run", FALSE);
	animControler->CreateTransition("Run", "Jump", "JumpTrigger", TRUE);
	animControler->CreateTransition("Run", "FallIdle", "OnGround", FALSE);

	//Jumpからの移行
	animControler->CreateNotLoopAnimExitTransition("Jump", "FallIdle");

	//FallIdleからの移行
	animControler->CreateTransition("FallIdle", "Idle", "OnGround", TRUE);

	AddComponent<PlayerAnimationControlComponent>();

	AddComponent<CapsuleColliderComponent>();

	AddComponent<RigidBodyComponent>();

	AddComponent<MoveTestComponent>();


	//子オブジェクトとしてカメラを作成
	{
		//ゲームオブジェクト生成
		GameObject* child = AddChild("Camera");
		child->GetTransFormComponent()->SetPosition(XMFLOAT3(0.0f, 150.0f, -300.0f));

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
