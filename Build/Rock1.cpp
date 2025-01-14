#include "Rock1.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "primitivecomponent.h"
#include "renderer.h"
Rock1::Rock1(Scene* scene)
{
	this->pScene = scene;
}

Rock1::~Rock1()
{
}

void Rock1::Awake(void)
{
	GameObject::Awake();

	LoadFbxFileMesh("Rock_1.fbx");
	BoxColliderComponent* box = AddComponent<BoxColliderComponent>();
	box->SetBox(XMFLOAT3(550.0f, 300.0f, 300.0f));
	RigidBodyComponent* rb = AddComponent<RigidBodyComponent>();
	rb->SetIsStatic(TRUE);

}
