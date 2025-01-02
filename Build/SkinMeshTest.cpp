#include "SkinMeshTest.h"
#include "transformcomponent.h"
#include "AnimationControlerComponent.h"
#include "MoveTestComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
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
	SetName("SkinMesh");
	this->transformComponent->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	this->transformComponent->SetScale(XMFLOAT3(0.1f, 0.1f, 0.1f));
	//this->transformComponent->RotWorldYaw(XM_PIDIV2);

	this->LoadFbxFileSkinMesh("aqchan.fbx");

	AnimationControlerComponent* animControler = this->AddComponent<AnimationControlerComponent>();
	animControler->LoadDefaulAnimation("aqchansneakRun.fbx", "Idol");
	//animControler->LoadAnimation("Lex_Bite.fbx", "Atack", FALSE);
	//AnimParameter para;
	//para.value = FALSE;
	//para.isTrigger = TRUE;
	//animControler->CreateCondition("AtackTrigger", para);
	//animControler->CreateTransition("Idol", "Atack", "AtackTrigger", TRUE);
	//animControler->CreateNotLoopAnimExitTransition("Atack", "Idol");

	AddComponent<BoxColliderComponent>()->SetBox(XMFLOAT3(10.0f, 10.0f, 10.0f));

	AddComponent<RigidBodyComponent>();

	AddComponent<MoveTestComponent>();
}
