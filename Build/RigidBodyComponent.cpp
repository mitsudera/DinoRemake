#include "RigidBodyComponent.h"
#include "gameobject.h"
#include "transformcomponent.h"
#include "GameEngine.h"
#include "TerrainComponent.h"
#include "PhysixEngine.h"
RigidBodyComponent::RigidBodyComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}

RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::Awake(void)
{
	Component::Awake();
    pPhysxEngine = pGameEngine->GetPhysixEngine();

    useGravity = TRUE;
    mass = 1.0f;
    drag = 0.1f;
}

void RigidBodyComponent::Init(void)
{
	Component::Init();
	transform = GetTransFormComponent();

}

void RigidBodyComponent::Update(void)
{
    Component::Update();


}

void RigidBodyComponent::LateUpdate(void)
{
    Component::LateUpdate();
}

void RigidBodyComponent::Uninit(void)
{
	Component::Uninit();
}

void RigidBodyComponent::OnEnable(void)
{
	Component::OnEnable();

}

void RigidBodyComponent::OnDisable(void)
{
	Component::OnDisable();
}

void RigidBodyComponent::SetMass(float f)
{
	mass = f;
}

void RigidBodyComponent::SetDrag(float f)
{
	drag = f;
}

void RigidBodyComponent::SetAngularDrag(float f)
{
	angularDrag = f;
}

void RigidBodyComponent::SetUseGarvity(BOOL b)
{
	useGravity = b;
}

void RigidBodyComponent::SetIsKinematic(BOOL b)
{
	isKinematic = b;
}

void RigidBodyComponent::AddForce(XMVECTOR force)
{
	velocity += force;
}
