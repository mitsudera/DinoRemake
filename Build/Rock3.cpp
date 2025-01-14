#include "Rock3.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "primitivecomponent.h"
#include "renderer.h"
Rock3::Rock3(Scene* scene)
{
	this->pScene = scene;
}

Rock3::~Rock3()
{
}

void Rock3::Awake(void)
{
	GameObject::Awake();

	LoadFbxFileMesh("Rock_3.fbx");
	BoxColliderComponent* box = AddComponent<BoxColliderComponent>();
	box->SetBox(XMFLOAT3(300.0f, 1000.0f, 300.0f));
	AddComponent<RigidBodyComponent>()->SetIsStatic(TRUE);

}
