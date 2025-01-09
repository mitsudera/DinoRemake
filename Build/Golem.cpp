#include "Golem.h"
#include "transformcomponent.h"
#include "SphereColliderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "GolemComponent.h"
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

	RigidBodyComponent* rb = AddComponent<RigidBodyComponent>();

	rb->SetDrag(0.1f);
	rb->SetMass(500.0f);


	this->LoadFbxFileSkinMesh("EnemyGolem.fbx");

	AddComponent<GolemComponent>();

}
