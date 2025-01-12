#include "Golem.h"
#include "transformcomponent.h"
#include "SphereColliderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "GolemComponent.h"
#include "AnimationControlerComponent.h"
#include "AttackComponent.h"
#include "RotBoxColliderComponent.h"
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

	RotBoxColliderComponent* box = AddComponent<RotBoxColliderComponent>();
	box->SetRotBox(XMFLOAT3(100.0f, 300.0f, 100.0f));
	box->SetPivot(XMFLOAT3(0.0f, 150.0f, 0.0f));

	RigidBodyComponent* rb = AddComponent<RigidBodyComponent>();

	rb->SetDrag(0.1f);
	rb->SetMass(500.0f);


	this->LoadFbxFileSkinMesh("EnemyGolem.fbx");

	AnimationControlerComponent* animControler = AddComponent<AnimationControlerComponent>();
	animControler->LoadDefaulAnimation("GolemIdle.fbx", "Idle");
	animControler->LoadAnimation("GolemWalk.fbx", "Walk", TRUE);
	animControler->LoadAnimation("GolemAttack1.fbx", "Attack1", FALSE);

	//アニメーショントランジション用パラメータの設定
	//bool
	AnimParameter para;
	para.value = FALSE;
	para.isTrigger = FALSE;
	animControler->CreateCondition("Walk", para);

	//trigger
	para.value = FALSE;
	para.isTrigger = TRUE;
	animControler->CreateCondition("Attack", para);

	//トランジションの設定
	//追加した順番が優先順位になる
	//idolからの移行
	animControler->CreateTransition("Idle", "Attack1", "Attack", TRUE);
	animControler->CreateTransition("Idle", "Walk", "Walk", TRUE);

	//walk
	animControler->CreateTransition("Walk", "Attack1", "Attack", TRUE);
	animControler->CreateTransition("Walk", "Idle", "Walk", FALSE);

	//Attack
	animControler->CreateNotLoopAnimExitTransition("Attack1", "Idle");
	

	//weapon
	GameObject* rHand = SerchAllChild("B-hand.L")->AddChild("rHand");
	rHand->SetTag(ObjectTag::EnemyAttack);
	AttackComponent* rAttack = rHand->AddComponent<AttackComponent>();
	BoxColliderComponent* rHandCollider = rHand->AddComponent<BoxColliderComponent>();
	rHandCollider->SetBox(XMFLOAT3(60.0f, 60.0f, 60.0f));

	GameObject* lHand = SerchAllChild("B-hand.R")->AddChild("lHand");
	lHand->SetTag(ObjectTag::EnemyAttack);
	AttackComponent* lAttack = lHand->AddComponent<AttackComponent>();
	BoxColliderComponent* lHandCollider = lHand->AddComponent<BoxColliderComponent>();
	lHandCollider->SetBox(XMFLOAT3(60.0f, 60.0f, 60.0f));


	AddComponent<GolemComponent>()->SetAttack(rAttack,lAttack);

}
