#include "Rock1.h"
#include "RotBoxColliderComponent.h"
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
	RotBoxColliderComponent* box = AddComponent<RotBoxColliderComponent>();
	box->SetRotBox(XMFLOAT3(550.0f, 350.0f, 300.0f));
	AddComponent<RigidBodyComponent>()->SetIsStatic(TRUE);

}
