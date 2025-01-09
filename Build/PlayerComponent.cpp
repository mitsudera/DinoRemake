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
#include "SkinMeshLinkerComponent.h"
#include "ColliderComponent.h"
#include "AttackComponent.h"
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
	speed = 100.0f;
	jumpForce = 500.0f;
}

void PlayerComponent::Init(void)
{
	Component::Init();
	control = TRUE;
	animControl = GetComponent<PlayerAnimationControlComponent>();
	transform = GetTransFormComponent();
	rb = GetComponent<RigidBodyComponent>();
	linker = GetComponent<SkinMeshLinkerComponent>();
	collider = GetComponent<ColliderComponent>();

	linker->SetSpring("J_Sec_L_Bust1", 0.7f, 400.0f, 10.0f);
	linker->SetSpring("J_Sec_R_Bust1", 0.7f, 400.0f, 10.0f);
	linker->SetSpring("J_Sec_L_Bust2", 0.5f, 500.0f, 10.0f);
	linker->SetSpring("J_Sec_R_Bust2", 0.5f, 500.0f, 10.0f);

	atkCom = pGameObject->SerchAllChild("weapon")->GetComponent<AttackComponent>();
	combo = 0;
	attackCnt = 0.0f;
	onAttack = FALSE;



}

void PlayerComponent::Uninit(void)
{
	Component::Uninit();
}

void PlayerComponent::Update(void)
{
	Component::Update();

	state = PlayerState::Idle;
	XMVECTOR playerFront = transform->GetAxisZ();


	if (control)
	{
		if (!onAttack)
		{
			if (input->GetLeftStickY(0) < -950)
			{

				state = PlayerState::Run;


				velocity = speed * pGameEngine->GetDeltaTime() * 4.0f;

				rb->MovePosition(playerFront, velocity);



			}
			else
			{

				if (input->GetLeftStickY(0) != 0 || input->GetLeftStickX(0) != 0)
				{
					state = PlayerState::Walk;
					velocity = speed * pGameEngine->GetDeltaTime();

					int x = input->GetLeftStickX(0);
					int y = input->GetLeftStickY(0);
					float angle = GetAngleInRadiansFromVector(XMFLOAT2(-y, x));

					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);

				}



			}


			if (input->GetKeyboardPress(DIK_LSHIFT) && input->GetKeyboardPress(DIK_W))
			{

				state = PlayerState::Run;


				velocity = speed * pGameEngine->GetDeltaTime() * 4.0f;

				rb->MovePosition(playerFront, velocity);



			}
			else
			{

				if (input->GetKeyboardPress(DIK_W) || input->GetKeyboardPress(DIK_D) || input->GetKeyboardPress(DIK_S) || input->GetKeyboardPress(DIK_A))
				{
					state = PlayerState::Walk;

				}

				velocity = speed * pGameEngine->GetDeltaTime();

				if (input->GetKeyboardPress(DIK_W) && input->GetKeyboardPress(DIK_D))
				{
					float angle = XM_PIDIV4 * 1.0f;

					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);

				}
				else if (input->GetKeyboardPress(DIK_D) && input->GetKeyboardPress(DIK_S))
				{
					float angle = XM_PIDIV4 * 3.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);


				}
				else if (input->GetKeyboardPress(DIK_S) && input->GetKeyboardPress(DIK_A))
				{
					float angle = XM_PIDIV4 * 5.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);




				}
				else if (input->GetKeyboardPress(DIK_A) && input->GetKeyboardPress(DIK_W))
				{
					float angle = XM_PIDIV4 * 7.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);




				}
				else if (input->GetKeyboardPress(DIK_W))
				{
					float angle = 0.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);



				}
				else if (input->GetKeyboardPress(DIK_D))
				{
					float angle = XM_PIDIV2 * 1.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);



				}
				else if (input->GetKeyboardPress(DIK_S))
				{
					float angle = XM_PIDIV2 * 2.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);



				}
				else if (input->GetKeyboardPress(DIK_A))
				{
					float angle = XM_PIDIV2 * 3.0f;
					XMVECTOR vec = XMVector3Rotate(playerFront, XMQuaternionRotationAxis(yonevec(), angle));
					rb->MovePosition(vec, velocity);
					animControl->SetAngle(angle);




				}

			}

			if (rb->GetOnGround())
			{
				if (input->GetKeyboardTrigger(DIK_SPACE) || input->IsButtonTriggered(0, BUTTON_X))
				{
					rb->AddForce(transform->GetAxisY() * jumpForce);

				}


			}

		}



		if (input->GetKeyboardPress(DIK_Z))
		{
			GetTransFormComponent()->RotYaw(-(XM_PI / 180));

		}
		else if (input->GetKeyboardPress(DIK_C))
		{
			GetTransFormComponent()->RotYaw((XM_PI / 180));

		}





	}

	if (rb->GetOnGround())
	{

		if (onAttack)
		{
			attackCnt += pGameEngine->GetDeltaTime();
		}
		else
		{
			attackCnt = 0.0f;
		}
		switch (combo)
		{
		case 0:
		{
			if (!animControl->GetIsTransition())
			{
				if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_B))
				{
					animControl->AttackTrigger();
					onAttack = TRUE;
					atkCom->SetAttack(5, 0.8f);
					combo = 1;
				}

			}



			break;
		}
		case 1:
		{
			if (attackCnt > 0.8f && attackCnt <= 1.0f)
			{
				if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_B))
				{
					animControl->AttackTrigger();
					onAttack = TRUE;
					atkCom->SetAttack(5, 0.8f);

					combo = 2;
				}
			}
			else if (attackCnt > 1.0f)
			{
				onAttack = FALSE;
				combo = 0;
			}

			break;
		}

		case 2:
		{
			if (attackCnt > 0.8f && attackCnt <= 1.0f)
			{
				if (input->GetKeyboardTrigger(DIK_RETURN) || input->IsButtonTriggered(0, BUTTON_B))
				{
					//animControl->AttackTrigger();
					//onAttack = TRUE;
					//atkCom->SetAttack(5, 0.75f);

					//combo++;
				}
			}
			else if (attackCnt > 1.0f)
			{
				onAttack = FALSE;
				combo = 0;
			}

			break;
		}

		default:
			break;
		}

	}

	if (collider->GetHitTag(GameObject::ObjectTag::Enemy))
	{
		GameObject* enemy = collider->GetHitTagObject(GameObject::ObjectTag::Enemy);
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

