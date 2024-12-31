#include "RigidBodyComponent.h"
#include "gameobject.h"
#include "transformcomponent.h"
#include "ColliderComponent.h"
#include "GameEngine.h"
#include "TerrainComponent.h"
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
    useGravity = TRUE;
    mass = 1.0f;
    drag = 0.1f;
}

void RigidBodyComponent::Init(void)
{
	Component::Init();
	transform = GetTransFormComponent();
	collider = pGameObject->GetComponent<ColliderComponent>();

}

void RigidBodyComponent::Update(void)
{
    Component::Update();


}

void RigidBodyComponent::LateUpdate(void)
{
    Component::LateUpdate();
    // �d�͂̓K�p
    if (useGravity)
    {
        XMVECTOR gravity = XMVectorSet(0.0f, -9.81f, 0.0f, 0.0f); // �W���d��
        velocity += gravity * pGameEngine->GetDeltaTime();

    }

    // ��C��R�̓K�p
    XMVECTOR dragForce = velocity * drag * -1.0f;
    velocity += dragForce * pGameEngine->GetDeltaTime();

    // ���ʂ��l���������x�X�V
    XMVECTOR acceleration = dragForce / mass;
    velocity += acceleration * pGameEngine->GetDeltaTime();

    // Transform�̍X�V
    transform->MoveVelocity(velocity * pGameEngine->GetDeltaTime());

    if (collider->GetHitTag(GameObject::ObjectTag::Field))
    {
        transform->SetPosY(collider->GetHitTagObject(GameObject::ObjectTag::Field)->GetComponent<TerrainComponent>()->GetHeight(transform->GetWorldPos()));
    }

}

void RigidBodyComponent::Uninit(void)
{
	Component::Uninit();
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
