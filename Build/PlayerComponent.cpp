#include "PlayerComponent.h"
#include "input.h"
#include "transformcomponent.h"
#include "AnimationControlerComponent.h"
#include "gameobject.h"
#include "Scene.h"
#include "TerrainComponent.h"
#include "ColliderComponent.h"
PlayerComponent::PlayerComponent(GameObject* gameObject)
{
	pGameObject = gameObject;
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Awake(void)
{
	Component::Awake();
}

void PlayerComponent::Init(void)
{
	Component::Init();
	control = TRUE;
	PlayerOffset = 2.0f;
}

void PlayerComponent::Uninit(void)
{
	Component::Uninit();
}

void PlayerComponent::Update(void)
{
	Component::Update();

	if (control)
	{
		if (input->GetKeyboardPress(DIK_W))
		{
			GetTransFormComponent()->MoveZAxis(1.0f);
		}
		if (input->GetKeyboardPress(DIK_S))
		{
			GetTransFormComponent()->MoveZAxis(-1.0f);

		}
		if (input->GetKeyboardPress(DIK_A))
		{
			GetTransFormComponent()->MoveXAxis(-1.0f);
		}
		if (input->GetKeyboardPress(DIK_D))
		{
			GetTransFormComponent()->MoveXAxis(1.0f);
		}

		//if (input->GetKeyboardPress(DIK_E))
		//{
		//	GetTransFormComponent()->MoveYAxis(1.0f);
		//}
		//if (input->GetKeyboardPress(DIK_Q))
		//{
		//	GetTransFormComponent()->MoveYAxis(-1.0f);
		//}

		if (input->GetKeyboardPress(DIK_Z))
		{
			GetTransFormComponent()->RotYaw(-(XM_PI / 180));

		}
		if (input->GetKeyboardPress(DIK_C))
		{
			GetTransFormComponent()->RotYaw((XM_PI / 180));

		}


	}
	if (input->GetKeyboardPress(DIK_1))
	{
		GetComponent<AnimationControlerComponent>()->SetCondition("AtackTrigger",TRUE);
	}

	float height = PlayerOffset + pGameObject->GetScene()->GetGameObjectName("Field")->GetComponent<TerrainComponent>()->GetHeight(GetTransFormComponent()->GetWorldPos());


	ColliderComponent* collider = GetComponent<ColliderComponent>();

	BOOL eHit= collider->GetHitTag(GameObject::ObjectTag::Enemy);
	//if (eHit)
	//{
	//	this->PlayerOffset = 1.0f;
	//}
	//else
	//{
	//	this->PlayerOffset = 2.0f;
	//}
}

void PlayerComponent::SetContorol(BOOL enable)
{
	control = enable;
}

void PlayerComponent::SetOffSet(float f)
{
	PlayerOffset = f;
}
