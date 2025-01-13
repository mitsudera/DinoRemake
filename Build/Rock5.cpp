#include "Rock5.h"
#include "RotBoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "primitivecomponent.h"
#include "renderer.h"
Rock5::Rock5(Scene* scene)
{
	this->pScene = scene;
}

Rock5::~Rock5()
{
}

void Rock5::Awake(void)
{
	GameObject::Awake();

	LoadFbxFileMesh("Rock_5.fbx");
	RotBoxColliderComponent* box = AddComponent<RotBoxColliderComponent>();
	box->SetRotBox(XMFLOAT3(250.0f, 500.0f, 250.0f));
	AddComponent<RigidBodyComponent>()->SetIsStatic(TRUE);

}
