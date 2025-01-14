#include "InvisibleWall.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "primitivecomponent.h"
#include "renderer.h"
InvisibleWall::InvisibleWall(Scene* scene)
{
	this->pScene = scene;
}

InvisibleWall::~InvisibleWall()
{
}

void InvisibleWall::Awake(void)
{
	GameObject::Awake();

	BoxColliderComponent* box = AddComponent<BoxColliderComponent>();
	box->SetBox(XMFLOAT3(1024*16.0f, 10000.0f, 300.0f));
	AddComponent<RigidBodyComponent>()->SetIsStatic(TRUE);

}
