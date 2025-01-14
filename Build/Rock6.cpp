#include "Rock6.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "primitivecomponent.h"
#include "renderer.h"
Rock6::Rock6(Scene* scene)
{
	this->pScene = scene;
}

Rock6::~Rock6()
{
}

void Rock6::Awake(void)
{
	GameObject::Awake();

	LoadFbxFileMesh("Rock_6.fbx");
	BoxColliderComponent* box = AddComponent<BoxColliderComponent>();
	box->SetBox(XMFLOAT3(330.0f, 1000.0f, 450.0f));
	AddComponent<RigidBodyComponent>()->SetIsStatic(TRUE);

}
