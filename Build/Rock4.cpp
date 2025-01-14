#include "Rock4.h"
#include "BoxColliderComponent.h"
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
	BoxColliderComponent* box = AddComponent<BoxColliderComponent>();
	box->SetBox(XMFLOAT3(550.0f, 1000.0f, 350.0f));
	AddComponent<RigidBodyComponent>()->SetIsStatic(TRUE);

}
