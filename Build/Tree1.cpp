#include "Tree1.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "primitivecomponent.h"
#include "renderer.h"
Tree1::Tree1(Scene* scene)
{
	this->pScene = scene;
}

Tree1::~Tree1()
{
}

void Tree1::Awake(void)
{
	GameObject::Awake();

	LoadFbxFileMesh("Tree1.fbx");
	BoxColliderComponent* box = AddComponent<BoxColliderComponent>();
	box->SetBox(XMFLOAT3(80.0f, 1000.0f, 80.0f));
	box->SetPivot(XMFLOAT3(0.0f, 500.0f, 0.0f));
	AddComponent<RigidBodyComponent>()->SetIsStatic(TRUE);
	PrimitiveComponent*pc= SerchAllChild("LOD0")->GetComponent<PrimitiveComponent>();
	pc->SetCullingMode(CULL_MODE::CULL_MODE_NONE);
	pc->SetAlphaTest(TRUE);

}
