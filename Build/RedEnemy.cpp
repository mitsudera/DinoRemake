#include "RedEnemy.h"
#include "transformcomponent.h"
#include "SphereColliderComponent.h"
#include "BoxColliderComponent.h"

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
	SetName("Akamaru");
	this->transformComponent->SetPosition(XMFLOAT3(0.0f, 0.0f, 10.0f));
	this->transformComponent->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));

	AddComponent<BoxColliderComponent>()->SetBox(XMFLOAT3(1.0f, 1.0f, 1.0f));

	this->LoadFbxFileMesh("Akamaru.fbx");


}
