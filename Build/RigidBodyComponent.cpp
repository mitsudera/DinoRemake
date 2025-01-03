#include "RigidBodyComponent.h"
#include "gameobject.h"
#include "transformcomponent.h"
#include "GameEngine.h"
#include "TerrainComponent.h"
#include "ColliderComponent.h"

constexpr XMFLOAT3 gravity = XMFLOAT3(0.0f, -9.81f, 0.0f); // �W���d��


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
	collider = pGameObject->GetComponent<ColliderComponent>();
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
	// �d�͂̓K�p
	if (useGravity)
	{
		XMVECTOR gravityV = XMLoadFloat3(&gravity); // �W���d��
		velocity += gravityV * pGameEngine->GetDeltaTime();
	}

	// ��C��R�̓K�p
	XMVECTOR dragForce = velocity * drag * -1.0f;
	velocity += dragForce * pGameEngine->GetDeltaTime();

	// ���ʂ��l���������x�X�V
	XMVECTOR acceleration = dragForce / mass;
	velocity += acceleration * pGameEngine->GetDeltaTime();

	transform->MoveVelocity(velocity * pGameEngine->GetDeltaTime());
	if (collider->GetHitTag(GameObject::ObjectTag::Field))
	{
		float h = collider->GetHitTagObject(GameObject::ObjectTag::Field)->GetComponent<TerrainComponent>()->GetHeight(GetWorldPos());
		if (transform->GetWorldPos().y > h)
		{
			onGround = FALSE;
		}
		else
		{
			transform->SetPosY(h);
			onGround = TRUE;

		}
	}
	else
	{
		onGround = FALSE;
	}


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

BOOL RigidBodyComponent::GetOnGround(void)
{
	return this->onGround;
}
