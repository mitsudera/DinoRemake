#include "TitlePlayer.h"
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
#include "BoxColliderComponent.h"
#include "RotBoxColliderComponent.h"
#include "AttackComponent.h"
#include "SpriteComponent.h"
#include "SoundSpeakerComponent.h"
TitlePlayer::TitlePlayer(Scene* scene)
{
	pScene = scene;
}

TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::Awake(void)
{
	GameObject::Awake();
	this->name = "TitlePlayer";
	this->tag = ObjectTag::Player;
	this->transformComponent->SetPosition(XMFLOAT3(0.0f, 0.0f, 200.0f));
	this->transformComponent->SetRotation(XMFLOAT3(0.0f, XM_PI, 0.0f));

	this->LoadFbxFileSkinMesh("Player2.fbx");

	AnimationControlerComponent* animControler = this->AddComponent<AnimationControlerComponent>();

	animControler->LoadDefaulAnimation("PlayerIdle.fbx", "Idle");


	CapsuleColliderComponent* box = AddComponent<CapsuleColliderComponent>();
	box->SetCapsule(XMFLOAT3(0.0f, 20.0f, 0.0f),XMFLOAT3(0.0f,160.0f,0.0f),20.0f);

	RigidBodyComponent* rb = AddComponent<RigidBodyComponent>();

	rb->SetDrag(0.1f);
	rb->SetMass(5000.0f);
	rb->SetIsStatic(FALSE);

	SoundSpeakerComponent* soundSpeaker = AddComponent<SoundSpeakerComponent>();



}
