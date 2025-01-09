#include "Player.h"
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
#include "PlayerComponent.h"
#include "BoxColliderComponent.h"
#include "AttackComponent.h"
Player::Player(Scene* scene)
{
	pScene = scene;
}

Player::~Player()
{
}

void Player::Awake(void)
{
	GameObject::Awake();
	this->name = "Player";
	this->tag = ObjectTag::Player;
	this->transformComponent->SetPosition(XMFLOAT3(0.0f, 10.0f, 0.0f));
	this->transformComponent->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));

	this->LoadFbxFileSkinMesh("Player2.fbx");

	SerchAllChild("J_Bip_L_Index1")->SetNotAnim(TRUE);
	SerchAllChild("J_Bip_L_Little1")->SetNotAnim(TRUE);
	SerchAllChild("J_Bip_L_Middle1")->SetNotAnim(TRUE);
	SerchAllChild("J_Bip_L_Ring1")->SetNotAnim(TRUE);
	SerchAllChild("J_Bip_L_Thumb1")->SetNotAnim(TRUE);


	AnimationControlerComponent* animControler = this->AddComponent<AnimationControlerComponent>();

	animControler->LoadDefaulAnimation("PlayerIdle.fbx", "Idle");

	animControler->LoadAnimation("PlayerWalk.fbx", "PlayerRightWalk.fbx", "PlayerBackWalk.fbx", "PlayerLeftWalk.fbx", "Walk", TRUE);

	animControler->LoadAnimation("PlayerRun.fbx", "Run", TRUE);
	animControler->LoadAnimation("PlayerFallIdle.fbx", "FallIdle", TRUE);
	animControler->LoadAnimation("PlayerAttack1.fbx", "Attack1", FALSE);
	animControler->LoadAnimation("PlayerAttack2.fbx", "Attack2", FALSE);

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
	animControler->CreateCondition("Attack", para);


	//トランジションの設定
	//idolからの移行
	animControler->CreateTransition("Idle", "Walk", "Walk", TRUE);
	animControler->CreateTransition("Idle", "Run", "Run", TRUE);
	animControler->CreateTransition("Idle", "FallIdle", "OnGround", FALSE);
	animControler->CreateTransition("Idle", "Attack1", "Attack", TRUE);

	//walkからの移行
	animControler->CreateTransition("Walk", "Idle", "Walk", FALSE);
	animControler->CreateTransition("Walk", "Run", "Run", TRUE);
	animControler->CreateTransition("Walk", "FallIdle", "OnGround", FALSE);
	animControler->CreateTransition("Walk", "Attack1", "Attack", TRUE);


	//Runからの移行
	animControler->CreateTransition("Run", "Walk", "Walk", TRUE);
	animControler->CreateTransition("Run", "Idle", "Run", FALSE);
	animControler->CreateTransition("Run", "FallIdle", "OnGround", FALSE);
	animControler->CreateTransition("Run", "Attack1", "Attack", TRUE);


	//FallIdleからの移行
	animControler->CreateTransition("FallIdle", "Idle", "OnGround", TRUE);

	//Attack1
	animControler->CreateNotLoopAnimExitTransition("Attack1", "Idle");
	animControler->CreateTransition("Attack1", "Attack2","Attack",TRUE);

	//Attack2
	animControler->CreateNotLoopAnimExitTransition("Attack2", "Idle");


	AddComponent<PlayerComponent>();

	AddComponent<PlayerAnimationControlComponent>();

	BoxColliderComponent* box = AddComponent<BoxColliderComponent>();
	box->SetBox(XMFLOAT3(50.0f, 160.0f, 50.0f));
	box->SetPivot(XMFLOAT3(0.0f, 80.0f, 0.0f));

	RigidBodyComponent* rb = AddComponent<RigidBodyComponent>();

	rb->SetDrag(0.1f);
	rb->SetMass(50.0f);

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
		cameraComponent->SetNear(10.0f);
		cameraComponent->SetFar(10000.0f);

		//エンジンのメインカメラにセット
		pGameEngine->SetMainCamera(cameraComponent);

	}

	//weapon
	GameObject* weapon = SerchAllChild("J_Bip_L_Hand")->AddChild("weapon");
	weapon->LoadFbxFileMesh("WeaponKatana.fbx");
	weapon->SetNotAnim(TRUE);
	TransformComponent* weaponTrans = weapon->GetTransFormComponent();
	weaponTrans->SetPosition(XMFLOAT3(4.166f, -1.822f, 2.484f));
	weaponTrans->RotWorldPitch(XM_PIDIV2);
	weaponTrans->RotWorldRoll(XM_PIDIV2);

	weapon->SetTag(ObjectTag::PlayerAttack);
	AttackComponent* atack = weapon->AddComponent<AttackComponent>();
	CapsuleColliderComponent* weaponCollider = weapon->AddComponent<CapsuleColliderComponent>();
	weaponCollider->SetCapsule(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 70.0f, 0.0f), 10.0f);


}
