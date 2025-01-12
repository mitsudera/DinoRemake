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
#include "RotBoxColliderComponent.h"
#include "AttackComponent.h"
#include "SpriteComponent.h"
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
	this->transformComponent->SetPosition(XMFLOAT3(0.0f, 1.0f, 0.0f));
	this->transformComponent->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));

	this->LoadFbxFileSkinMesh("Player2.fbx");

	SerchAllChild("J_Bip_L_Index1")->SetNotAnim(TRUE);
	SerchAllChild("J_Bip_L_Little1")->SetNotAnim(TRUE);
	SerchAllChild("J_Bip_L_Middle1")->SetNotAnim(TRUE);
	SerchAllChild("J_Bip_L_Ring1")->SetNotAnim(TRUE);
	SerchAllChild("J_Bip_L_Thumb1")->SetNotAnim(TRUE);


	AnimationControlerComponent* animControler = this->AddComponent<AnimationControlerComponent>();

	animControler->LoadDefaulAnimation("PlayerIdle.fbx", "Idle");

	//animControler->LoadAnimation("PlayerWalk.fbx", "PlayerRightWalk.fbx", "PlayerBackWalk.fbx", "PlayerLeftWalk.fbx", "Walk", TRUE);
	//animControler->LoadAnimation("PlayerDodgeForward.fbx", "PlayerDodgeRight.fbx", "PlayerDodgeLeft.fbx", "PlayerDodgeBack.fbx", "Dodge", FALSE);

	//animControler->LoadAnimation("PlayerRun.fbx", "Run", TRUE);
	//animControler->LoadAnimation("PlayerFallIdle.fbx", "FallIdle", TRUE);
	//animControler->LoadAnimation("PlayerAttack1.fbx", "Attack1", FALSE);
	//animControler->LoadAnimation("PlayerAttack2.fbx", "Attack2", FALSE);

	////アニメーショントランジション用パラメータの設定
	////bool
	//AnimParameter para;
	//para.value = FALSE;
	//para.isTrigger = FALSE;
	//animControler->CreateCondition("Walk", para);
	//animControler->CreateCondition("Run", para);
	//animControler->CreateCondition("OnGround", para);

	////trigger
	//para.value = FALSE;
	//para.isTrigger = TRUE;
	//animControler->CreateCondition("JumpTrigger", para);
	//animControler->CreateCondition("Attack", para);
	//animControler->CreateCondition("Dodge", para);


	////トランジションの設定
	////追加した順番が優先順位になる
	////idolからの移行
	//animControler->CreateTransition("Idle", "FallIdle", "OnGround", FALSE);
	//animControler->CreateTransition("Idle", "Attack1", "Attack", TRUE);
	//animControler->CreateTransition("Idle", "Dodge", "Dodge", TRUE,0.1f);
	//animControler->CreateTransition("Idle", "Run", "Run", TRUE);
	//animControler->CreateTransition("Idle", "Walk", "Walk", TRUE);

	////walkからの移行
	//animControler->CreateTransition("Walk", "FallIdle", "OnGround", FALSE);
	//animControler->CreateTransition("Walk", "Attack1", "Attack", TRUE);
	//animControler->CreateTransition("Walk", "Dodge", "Dodge", TRUE,0.1f);
	//animControler->CreateTransition("Walk", "Run", "Run", TRUE);
	//animControler->CreateTransition("Walk", "Idle", "Walk", FALSE);


	////Runからの移行
	//animControler->CreateTransition("Run", "FallIdle", "OnGround", FALSE);
	//animControler->CreateTransition("Run", "Attack1", "Attack", TRUE);
	//animControler->CreateTransition("Run", "Dodge", "Dodge", TRUE, 0.1f);
	//animControler->CreateTransition("Run", "Walk", "Walk", TRUE);
	//animControler->CreateTransition("Run", "Idle", "Run", FALSE);


	////FallIdleからの移行
	//animControler->CreateTransition("FallIdle", "Idle", "OnGround", TRUE);

	////Attack1
	//animControler->CreateTransition("Attack1", "Attack2","Attack",TRUE);
	//animControler->CreateTransition("Attack1", "Dodge", "Dodge",TRUE, 0.1f);
	//animControler->CreateNotLoopAnimExitTransition("Attack1", "Idle");

	////Attack2
	//animControler->CreateTransition("Attack2", "Attack1", "Attack", TRUE);
	//animControler->CreateTransition("Attack2", "Dodge", "Dodge", TRUE, 0.1f);
	//animControler->CreateNotLoopAnimExitTransition("Attack2", "Idle");

	////dodge
	//animControler->CreateTransition("dodge", "Attack1", "Attack", TRUE);
	//animControler->CreateNotLoopAnimExitTransition("Dodge", "Idle");


	AddComponent<PlayerComponent>();

	AddComponent<PlayerAnimationControlComponent>();

	RotBoxColliderComponent* box = AddComponent<RotBoxColliderComponent>();
	box->SetRotBox(XMFLOAT3(50.0f, 160.0f, 50.0f));
	box->SetPivot(XMFLOAT3(0.0f, 80.0f, 0.0f));

	RigidBodyComponent* rb = AddComponent<RigidBodyComponent>();

	rb->SetDrag(0.1f);
	rb->SetMass(5000.0f);
	rb->SetIsStatic(FALSE);



	//子オブジェクトとしてカメラを作成
	{
		//注視点用オブジェクト
		GameObject* camat = AddChild("CameraAt");
		camat->GetTransFormComponent()->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));


		//ゲームオブジェクト生成
		GameObject* child = camat->AddChild("Camera");
		child->GetTransFormComponent()->SetPosition(XMFLOAT3(0.0f, 150.0f, -300.0f));

		//カメラコンポーネントの生成
		CameraComponent* cameraComponent = child->AddComponent<CameraComponent>();
		cameraComponent->Init();
		cameraComponent->SetRenderTarget(pScene->GetGameEngine()->GetRenderer()->GetBackBuffer());
		cameraComponent->SetDepthStencilView(pScene->GetGameEngine()->GetRenderer()->GetBackBufferDSV());
		cameraComponent->SetSky(pScene->GetGameObject<SkySphere>());
		cameraComponent->SetTrackingMode(CameraComponent::TrackingMode::NONE);
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

	{//ui
		GameObject* playerUI = AddChild("PlayerUI");
		GameObject* hpFrame = playerUI->AddChild("HPFrame");
		GameObject* hpLine = playerUI->AddChild("HPLine");
		hpFrame->AddComponent<SpriteComponent>();
		hpLine->AddComponent<SpriteComponent>();
	}

}
