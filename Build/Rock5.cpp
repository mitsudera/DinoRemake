#include "Rock5.h"
#include "BoxColliderComponent.h"
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
	BoxColliderComponent* box = AddComponent<BoxColliderComponent>();
	box->SetBox(XMFLOAT3(350.0f, 1000.0f, 250.0f));
	box->SetPivot(XMFLOAT3(-20.0f, 0.0f, 40.0f));
	AddComponent<RigidBodyComponent>()->SetIsStatic(TRUE);

}
