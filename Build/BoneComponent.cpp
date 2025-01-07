#include "BoneComponent.h"
#include "SkinMeshTreeData.h"
#include "SkinMeshLinkerComponent.h"
#include "transformcomponent.h"
#include "gameobject.h"
#include "GameEngine.h"
#include "DebugUtility.h"
#include "CBufferManager.h"

constexpr XMFLOAT3 gravity = XMFLOAT3(0.0f, -9.81f, 0.0f); // 標準重力

BoneComponent::BoneComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}
BoneComponent::~BoneComponent()
{
}
void BoneComponent::Awake(void)
{
	Component::Awake();
	isPhysics = TRUE;
	joint = Joint::Standard;

}
void BoneComponent::Init(void)
{
	Component::Init();
	transform = GetTransFormComponent();
}
void BoneComponent::FixedUpdate(void)
{
	Component::FixedUpdate();
	if (this->isPhysics)
	{
		switch (joint)
		{
		case BoneComponent::Joint::Standard:
		{
			XMFLOAT3 parentBonePos = { 0.0f,0.0f,0.0f };
			// 重力の適用
			XMVECTOR gravityV = XMLoadFloat3(&gravity); // 標準重力
			velocity += gravityV * pGameEngine->GetFixedDeltaTime();


			// 空気抵抗の適用
			XMVECTOR dragForce = velocity * 0.1f * -1.0f;
			velocity += dragForce * pGameEngine->GetFixedDeltaTime();


			transform->MoveVelocity(velocity * pGameEngine->GetFixedDeltaTime());
			float h = 0.0f;
			if (transform->GetWorldPos().y <= h)
			{
				transform->SetWorldPosY(h);
				XMFLOAT3 p = GetWorldPos();
				// 摩擦の適用
				XMVECTOR frictionForce = velocity * 0.9f * -1.0f;
				velocity += frictionForce * pGameEngine->GetFixedDeltaTime();

			}


			break;

		}
		case BoneComponent::Joint::Spring:
		{
			break;

		}


		}
	}


}
void BoneComponent::LateUpdate(void)
{
	Component::LateUpdate();

}
void BoneComponent::DebugDraw(void)
{
	Component::DebugDraw();
	XMMATRIX world = XMMatrixIdentity();
	world = GetTransFormComponent()->GetWorldMtx(world);
	this->pGameEngine->GetCBufferManager()->SetWorldMtx(&world);

	pGameEngine->GetDebugUtility()->DrawDebugBox();

}
XMMATRIX BoneComponent::GetInitMtxInverse(void)
{
	return this->initMtxInv;
}
void BoneComponent::SetBone(BoneData* data, SkinMeshLinkerComponent* linker)
{
	if (data->GetParent()->GetAttribute() != SkinMeshTreeNode::Attribute::Bone)
	{
		isRoot = TRUE;
		this->parentBone = nullptr;
	}
	else
	{
		isRoot = FALSE;
		this->parentBone = pGameObject->GetParent()->GetComponent<BoneComponent>();
	}
	this->GetTransFormComponent()->SetLocalMtx(data->GetLocalOffset());

	this->initMtx = data->GetWorldOffset();
	this->initMtxInv = XMMatrixInverse(nullptr,initMtx);

	this->linker = linker;


	this->GetTransFormComponent()->UpdateMatrix();

	//this->initMtxInv = XMMatrixInverse(nullptr, GetTransFormComponent()->GetWorldMtx());


	linker->AddBone(this);

}

XMMATRIX& BoneComponent::GetBoneMtx(void)
{
	initMtx;
	XMMATRIX mtx = GetWorldMtx();
	XMFLOAT3 p = GetWorldPos();
	boneMtx = XMMatrixTranspose(XMMatrixMultiply(initMtxInv, GetWorldMtx()));
	this;
	return boneMtx;
}

void BoneComponent::SetIsPhysics(BOOL b)
{
	isPhysics = b;
}

BOOL BoneComponent::GetIsPhysics(void)
{
	return isPhysics;
}

void BoneComponent::SetJoint(Joint j)
{
	joint = j;
}

void BoneComponent::SetIsRoot(BOOL b)
{
	isRoot = b;
}

void BoneComponent::SetParentBone(BoneComponent* parent)
{
	this->parentBone = parent;
}

void BoneComponent::AddChild(GameObject* child)
{
	BoneComponent* bc = child->GetComponent<BoneComponent>();
	if (bc)
	{
		this->childArray.push_back(bc);

	}
}
