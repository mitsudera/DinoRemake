#include "RigidBodyComponent.h"
#include "gameobject.h"
#include "transformcomponent.h"
#include "GameEngine.h"
#include "TerrainComponent.h"
#include "ColliderComponent.h"

constexpr XMFLOAT3 gravity = XMFLOAT3(0.0f, -9.81f, 0.0f); // 標準重力
constexpr float onGroundFacter = 5.0f;

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
	worldPos = XMLoadFloat3(&transform->GetWorldPos());
	offGroundTime = 0.0f;
	groundLen = 0.0f;
	move = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

}

void RigidBodyComponent::FixedUpdate(void)
{
	Component::FixedUpdate();

	float deltaTime = pGameEngine->GetFixedDeltaTime();

	worldPos += move;

	// 重力の適用
	if (useGravity)
	{
		XMVECTOR gravityV = XMLoadFloat3(&gravity); // 標準重力
		velocity += gravityV * mass * deltaTime;
	}

	// 空気抵抗の適用
	XMVECTOR dragForce = velocity * drag * -1.0f;
	velocity += dragForce * deltaTime;

	worldPos += velocity * deltaTime;



	//地面との当たり判定を取得し座標修正
	if (collider->GetHitTag(GameObject::ObjectTag::Field))
	{
		float h = collider->GetHitTagObject(GameObject::ObjectTag::Field)->GetComponent<TerrainComponent>()->GetHeight(GetWorldPos());
		if (worldPos.m128_f32[1] > h)
		{
			onGround = FALSE;
			offGroundTime += deltaTime;
			groundLen = worldPos.m128_f32[1] - h;
		}
		else
		{

			worldPos.m128_f32[1] = h;
			velocity.m128_f32[1] = 0.0f;
			onGround = TRUE;
			offGroundTime = 0.0f;
			groundLen = 0.0f;
		}
	}
	else
	{
		onGround = FALSE;
	}

	transform->SetWorldPosition(worldPos);
	move = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

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

void RigidBodyComponent::SetFriction(float f)
{
	friction = f;
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

void RigidBodyComponent::MovePosition(XMVECTOR vec, float moveValue)
{
	move += vec * moveValue;
}

void RigidBodyComponent::MovePosition(XMFLOAT3 vec, float moveValue)
{
	MovePosition(XMLoadFloat3(&vec), moveValue);
}

float RigidBodyComponent::GetOffGroundTime(void)
{
	return offGroundTime;
}

float RigidBodyComponent::GetGroundLength(void)
{
	return groundLen;
}


BOOL RigidBodyComponent::GetOnGround(void)
{
	return this->onGround;
}
