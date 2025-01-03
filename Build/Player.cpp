#include "Player.h"
#include "MeshComponent.h"
#include "transformcomponent.h"
#include "CameraComponent.h"
#include "Scene.h"
#include "GameEngine.h"
#include "renderer.h"
#include "AnimationControlerComponent.h"
#include "PlayerComponent.h"
#include "SphereColliderComponent.h"
#include "CapsuleColliderComponent.h"
#include "SkySphere.h"

Player::Player(Scene* scene)
{
	this->pScene = scene;

}

Player::~Player()
{
}

void Player::Awake(void)
{

	GameObject::Awake();

	SetName("Player");
	this->transformComponent->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	this->transformComponent->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));

	this->LoadFbxFileMesh("PlayerRed.fbx");
	AnimationControlerComponent* animControler = this->AddComponent<AnimationControlerComponent>();
	animControler->LoadDefaulAnimation("PlayerIdol.fbx", "Idol");
	animControler->LoadAnimation("PlayerAtack.fbx", "Atack",FALSE);
	AnimParameter para;
	para.value = FALSE;
	para.isTrigger = TRUE;
	animControler->CreateCondition("AtackTrigger", para);
	animControler->CreateTransition("Idol", "Atack", "AtackTrigger", TRUE);
	animControler->CreateNotLoopAnimExitTransition("Atack", "Idol");

	PlayerComponent* playerCom = AddComponent<PlayerComponent>();
	playerCom->SetOffSet(2.0f);

	CapsuleColliderComponent* collider = AddComponent<CapsuleColliderComponent>();
	collider->SetCapsule(XMFLOAT3(0.0f, 3.0f, 0.0f), XMFLOAT3(0.0f, -3.0f, 0.0f), 1.0f);

	//子オブジェクトとしてカメラを作成
	{
		//ゲームオブジェクト生成
		GameObject* child = AddChild("Camera");
		child->GetTransFormComponent()->SetPosition(XMFLOAT3(0.0f, 10.0f, -15.0f));

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
