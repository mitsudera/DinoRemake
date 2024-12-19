#include "RedEnemy.h"
#include "transformcomponent.h"
#include "SphereColliderComponent.h"
#include "CapsuleColliderComponent.h"

RedEnemy::RedEnemy(Scene* scene)
{
	pScene = scene;
}

RedEnemy::~RedEnemy()
{
}

void RedEnemy::Awake(void)
{
	GameObject::Awake();

	this->tag = ObjectTag::Enemy;
	this->name = "Akamaru";
	this->transformComponent->SetPosition(XMFLOAT3(0.0f, 2.0f, 20.0f));
	this->transformComponent->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));

	CapsuleColliderComponent* collider= this->AddComponent<CapsuleColliderComponent>();
	collider->SetCapsule(XMFLOAT3(0.0f, 3.0f, 0.0f), XMFLOAT3(0.0f, -3.0f, 0.0f), 2.0f);

	this->LoadFbxFileMesh("Akamaru.fbx");


}
