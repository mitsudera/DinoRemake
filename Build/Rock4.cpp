#include "Rock4.h"
#include "RotBoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "primitivecomponent.h"
#include "renderer.h"
Rock4::Rock4(Scene* scene)
{
	this->pScene = scene;
}

Rock4::~Rock4()
{
}

void Rock4::Awake(void)
{
	GameObject::Awake();

	LoadFbxFileMesh("Rock_4.fbx");
	RotBoxColliderComponent* box = AddComponent<RotBoxColliderComponent>();
	box->SetRotBox(XMFLOAT3(500.0f, 300.0f, 370.0f));
	AddComponent<RigidBodyComponent>()->SetIsStatic(TRUE);

}
