#include "Golem.h"
#include "transformcomponent.h"
#include "SphereColliderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "GolemComponent.h"
#include "AnimationControlerComponent.h"
#include "AttackComponent.h"
#include "RotBoxColliderComponent.h"
#include "CapsuleColliderComponent.h"
#include "SphereColliderComponent.h"
#include "SoundSpeakerComponent.h"
Golem::Golem(Scene* scene)
{
	pScene = scene;
}

Golem::~Golem()
{
}

void Golem::Awake(void)
{
	GameObject::Awake();

	this->tag = ObjectTag::Enemy;
	this->name = "Golem";
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


	this->LoadFbxFileSkinMesh("EnemyGolem.fbx");

	AnimationControlerComponent* animControler = AddComponent<AnimationControlerComponent>();
	animControler->LoadDefaulAnimation("GolemIdle.fbx", "Idle");
	animControler->LoadAnimation("GolemWalk.fbx", "Walk", TRUE);
	animControler->LoadAnimation("GolemAttack1.fbx", "Attack1", FALSE);
	animControler->LoadAnimation("GolemDie.fbx", "Die", FALSE);

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
	speaker->LoadSound("punch.wav", "punch", SoundType::SE);
	//weapon
	GameObject* rHand = SerchAllChild("B-hand.L")->AddChild("rHand");
	rHand->SetTag(ObjectTag::EnemyAttack);
	AttackComponent* rAttack = rHand->AddComponent<AttackComponent>();
	rAttack->SetHitSound(speaker, "punch");
	SphereColliderComponent* rHandCollider = rHand->AddComponent<SphereColliderComponent>();
	rHandCollider->SetRadius(60.0f);

	GameObject* lHand = SerchAllChild("B-hand.R")->AddChild("lHand");
	lHand->SetTag(ObjectTag::EnemyAttack);
	AttackComponent* lAttack = lHand->AddComponent<AttackComponent>();
	lAttack->SetHitSound(speaker, "punch");
	SphereColliderComponent* lHandCollider = lHand->AddComponent<SphereColliderComponent>();
	lHandCollider->SetRadius(60.0f);



	AddComponent<GolemComponent>()->SetAttack(rAttack,lAttack);

}
