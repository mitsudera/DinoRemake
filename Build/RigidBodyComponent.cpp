#include "RigidBodyComponent.h"
#include "gameobject.h"
#include "transformcomponent.h"
#include "GameEngine.h"
#include "TerrainComponent.h"
#include "ColliderComponent.h"

constexpr XMFLOAT3 gravity = XMFLOAT3(0.0f, -9.81f, 0.0f); // 標準重力


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
	onGround = TRUE;
}

void RigidBodyComponent::Init(void)
{
	Component::Init();
	transform = GetTransFormComponent();

}

void RigidBodyComponent::FixedUpdate(void)
{
	Component::FixedUpdate();
	// 重力の適用
	if (useGravity)
	{
		XMVECTOR gravityV = XMLoadFloat3(&gravity); // 標準重力
		velocity += gravityV * mass * pGameEngine->GetFixedDeltaTime();
	}

	// 空気抵抗の適用
	XMVECTOR dragForce = velocity * drag * -1.0f;
	velocity += dragForce * pGameEngine->GetFixedDeltaTime();

	// 質量を考慮した速度更新
	XMVECTOR acceleration = dragForce / mass;
	velocity += acceleration * pGameEngine->GetFixedDeltaTime();

	transform->MoveVelocity(velocity * pGameEngine->GetFixedDeltaTime());
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

void RigidBodyComponent::Update(void)
{

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

void RigidBodyComponent::RotVelocityY(float f)
{
	XMVECTOR qton = XMQuaternionRotationAxis(yonevec(), f);

	velocity = XMVector3Rotate(velocity, qton);

}


BOOL RigidBodyComponent::GetOnGround(void)
{
	return this->onGround;
}
