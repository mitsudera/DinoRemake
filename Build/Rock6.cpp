#include "Rock6.h"
#include "RotBoxColliderComponent.h"
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
	RotBoxColliderComponent* box = AddComponent<RotBoxColliderComponent>();
	box->SetRotBox(XMFLOAT3(250.0f, 500.0f, 400.0f));
	AddComponent<RigidBodyComponent>()->SetIsStatic(TRUE);

}
