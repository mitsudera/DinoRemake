#include "Bear.h"
#include "transformcomponent.h"
#include "SphereColliderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "BearComponent.h"
#include "AnimationControlerComponent.h"
#include "AttackComponent.h"
#include "RotBoxColliderComponent.h"
#include "CapsuleColliderComponent.h"
#include "SphereColliderComponent.h"
#include "SoundSpeakerComponent.h"
Bear::Bear(Scene* scene)
{
	pScene = scene;
}

Bear::~Bear()
{
}

void Bear::Awake(void)
{
	GameObject::Awake();

	this->tag = ObjectTag::Enemy;
	this->name = "Bear";
	this->transformComponent->SetPosition(XMFLOAT3(0.0f, 0.0f, 200.0f));
	this->transformComponent->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));

	BoxColliderComponent* box = AddComponent<BoxColliderComponent>();
	box->SetBox(XMFLOAT3(100.0f, 300.0f, 100.0f));
	box->SetPivot(XMFLOAT3(0.0f, 150.0f, 0.0f));
	//CapsuleColliderComponent* box = AddComponent<CapsuleColliderComponent>();
	//box->SetCapsule(XMFLOAT3(0.0f, 100.0f, 0.0f), XMFLOAT3(0.0f, 300.0f, 0.0f), 100.0f);


	RigidBodyComponent* rb = AddComponent<RigidBodyComponent>();

	rb->SetDrag(0.1f);
	rb->SetMass(500.0f);


	this->LoadFbxFileSkinMesh("EnemyBear.fbx");

	AnimationControlerComponent* animControler = AddComponent<AnimationControlerComponent>();
	animControler->LoadDefaulAnimation("BearIdle.fbx", "Idle");
	animControler->LoadAnimation("BearWalk.fbx", "Walk", TRUE);
	animControler->LoadAnimation("BearAttack1.fbx", "Attack1", FALSE);
	animControler->LoadAnimation("BearDie.fbx", "Die", FALSE);

	//アニメーショントランジション用パラメータの設定
	//bool
	AnimParameter para;
	para.value = FALSE;
	para.isTrigger = FALSE;
	animControler->CreateCondition("Walk", para);
	animControler->CreateCondition("Die", para);

	//trigger
	para.value = FALSE;
	para.isTrigger = TRUE;
	animControler->CreateCondition("Attack", para);

	//トランジションの設定
	//追加した順番が優先順位になる
	//idolからの移行
	animControler->CreateTransition("Idle", "Die", "Die", TRUE);
	animControler->CreateTransition("Idle", "Attack1", "Attack", TRUE);
	animControler->CreateTransition("Idle", "Walk", "Walk", TRUE);

	//walk
	animControler->CreateTransition("Walk", "Die", "Die", TRUE);
	animControler->CreateTransition("Walk", "Attack1", "Attack", TRUE);
	animControler->CreateTransition("Walk", "Idle", "Walk", FALSE);

	//Attack
	animControler->CreateTransition("Attack1", "Die", "Die", TRUE);
	animControler->CreateNotLoopAnimExitTransition("Attack1", "Idle");




	SoundSpeakerComponent* speaker = AddComponent<SoundSpeakerComponent>();
	speaker->LoadSound("wolfatk.wav", "atk", SoundType::SE);
	//weapon
	GameObject* fung = SerchAllChild("Head_M")->AddChild("fung");
	fung->SetTag(ObjectTag::EnemyAttack);
	AttackComponent* fungAtk = fung->AddComponent<AttackComponent>();
	fungAtk->SetHitSound(speaker, "atk");
	SphereColliderComponent* rHandCollider = fung->AddComponent<SphereColliderComponent>();
	rHandCollider->SetRadius(60.0f);




	AddComponent<BearComponent>()->SetAttack(fungAtk);

}
