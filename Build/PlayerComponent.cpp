#include "PlayerComponent.h"
#include "input.h"
#include "transformcomponent.h"
#include "AnimationControlerComponent.h"
#include "gameobject.h"
#include "Scene.h"
#include "TerrainComponent.h"
#include "ColliderComponent.h"
#include "PlayerAnimationControlComponent.h"
#include "RigidBodyComponent.h"
#include "GameEngine.h"

constexpr float playerSpeed = 800.0f;
constexpr float jumpForce = 40.0f;

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
	animControl = GetComponent<PlayerAnimationControlComponent>();
	transform = GetTransFormComponent();
	rb = GetComponent<RigidBodyComponent>();
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
		if (rb->GetOnGround() == TRUE)
		{

			//if (input->GetKeyboardPress(DIK_LSHIFT))
			//{
			//	velocity = playerSpeed * pGameEngine->GetDeltaTime() * 2.0f;
			//}
			//else
			//{
			//	velocity = playerSpeed * pGameEngine->GetDeltaTime();

			//}

			if (input->GetKeyboardPress(DIK_W))
			{
				rb->AddForce(transform->GetAxisZ() * pGameEngine->GetDeltaTime() * playerSpeed);
				state = PlayerState::ForwardWalk;

			}
			else if (input->GetKeyboardPress(DIK_S))
			{
				rb->AddForce(-transform->GetAxisZ() * pGameEngine->GetDeltaTime() * playerSpeed);
				state = PlayerState::BackWalk;


			}
			else if (input->GetKeyboardPress(DIK_D))
			{
				rb->AddForce(transform->GetAxisX() * pGameEngine->GetDeltaTime() * playerSpeed);
				state = PlayerState::RightWalk;


			}
			else if (input->GetKeyboardPress(DIK_A))
			{
				rb->AddForce(-transform->GetAxisX() * pGameEngine->GetDeltaTime() * playerSpeed);
				state = PlayerState::LeftWalk;


			}
			else
			{
				state = PlayerState::Idle;

			}

			if (input->GetKeyboardPress(DIK_Z))
			{
				GetTransFormComponent()->RotYaw(-(XM_PI / 180));

			}
			else if (input->GetKeyboardPress(DIK_C))
			{
				GetTransFormComponent()->RotYaw((XM_PI / 180));

			}


			if (input->GetKeyboardTrigger(DIK_SPACE))
			{
				rb->AddForce(transform->GetAxisY() * jumpForce);
				state = PlayerState::Fall;
			}

		}
		else
		{

		}


	}


}

void PlayerComponent::SetContorol(BOOL enable)
{
	control = enable;
}

PlayerComponent::PlayerState PlayerComponent::GetState(void)
{
	return this->state;
}

